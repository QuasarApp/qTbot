//#
//# Copyright (C) 2018-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "itelegrambot.h"
#include "qTbot/messages/telegrammsg.h"
#include "qTbot/messages/telegramupdateanswer.h"
#include "qdir.h"
#include <QNetworkAccessManager>

#include <qTbot/requests/telegramgetfile.h>
#include <qTbot/requests/telegramgetme.h>
#include <qTbot/requests/telegramsendmsg.h>

#include <QNetworkReply>
#include <QSharedPointer>
#include <QDebug>

#include <qTbot/messages/telegramfile.h>

namespace qTbot {

ITelegramBot::ITelegramBot() {
    _manager = new QNetworkAccessManager();
    _manager->setAutoDeleteReplies(false);
}

ITelegramBot::~ITelegramBot() {
    delete _manager;
}

bool ITelegramBot::login(const QByteArray &token) {
    if (token.isEmpty()) {
        return false;
    }

    setToken(token);

    ITelegramBot::Responce cb = [this]( const QSharedPointer<iRequest>& ,
                                       const QSharedPointer<iMessage>& responce,
                                       int err) {

        if (err) {
            qDebug() << "Network error occured. code: " << err;
        }

        if (auto message = responce.dynamicCast<ITelegramMessage>()) {
            setId(message->rawJson().value("id").toInt());
            setName(message->rawJson().value("first_name").toString());
            setUsername(message->rawJson().value("username").toString());
        }
    };
    
    return sendRequest(QSharedPointer<TelegramGetMe>::create(), cb);
}

bool ITelegramBot::sendMessage(const QVariant &chatId, const QString &text) {
    return sendSpecificMessage(chatId.toLongLong(), text);
}

bool ITelegramBot::sendSpecificMessage(const QVariant & chatId,
                                       const QString &text,
                                       unsigned long long replyToMessageId,
                                       bool markdown,
                                       bool disableWebPagePreview,
                                       const Responce &cb) {

    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (text.isEmpty()) {
        return false;
    }

    auto msg = QSharedPointer<TelegramSendMsg>::create(chatId,
                                                       text,
                                                       replyToMessageId,
                                                       markdown,
                                                       disableWebPagePreview);
    return sendRequest(msg, cb);
}

QSharedPointer<iFile> ITelegramBot::getFile(const QString &fileId, iFile::Type fileType) {

    QSharedPointer<iFile> result = nullptr;

    if (fileId.isEmpty()) {
        return result;
    }

    auto localFilePath = findFileInlocatStorage(fileId);

    if (!localFilePath.isEmpty()) {

        if (fileType == iFile::Ram) {
            QFile localFile(localFilePath);
            if (localFile.open(QIODevice::ReadOnly)) {
                auto&& virtualFile = QSharedPointer<VirtualFile>::create(nullptr);
                virtualFile->setArray(localFile.readAll());
                localFile.close();

                result = virtualFile;
            }

        } else if (fileType == iFile::Local) {
            result = QSharedPointer<File>::create(nullptr, localFilePath);
        }

        result->setDownloadProgress(1);
        result->setFinished(true);
        return result;
    }

    auto msg = QSharedPointer<TelegramGetFile>::create(fileId);

    QDir().mkpath(defaultFileStorageLocation());

    localFilePath = defaultFileStorageLocation() + "/" + fileId;

    if (localFilePath.isEmpty())
        return result;

    if (auto &&replay = sendRequest(msg)) {
        // here i must be receive responce and prepare new request to file from the call back function.
        if (fileType == iFile::Ram) {
            result = QSharedPointer<VirtualFile>::create(replay);
        } else if (fileType == iFile::Local) {
            result = QSharedPointer<File>::create(replay, localFilePath);
        }
    }

    return result;
}

bool ITelegramBot::getFile(const QString &fileId,
                           std::function<void (const QSharedPointer<File> &)> cb) {

    if (auto&& ptr = getFile(fileId, iFile::Local)) {
        if (ptr->finished() && cb) {
            cb(ptr.dynamicCast<File>());
            return true;
        }

        connect(ptr.data(), &iFile::finishedChanged, [cb, ptr](){
            cb(ptr.dynamicCast<File>());
        });

        connect(ptr.data(), &iFile::errorChanged, [cb, ptr](){
            cb(ptr.dynamicCast<File>());
        });

        return true;
    }

    return false;
}

bool ITelegramBot::getFile(const QString &fileId,
                           std::function<void (const QSharedPointer<VirtualFile> &)> cb) {

    if (auto&& ptr = getFile(fileId, iFile::Local)) {
        if (ptr->finished() && cb) {
            cb(ptr.dynamicCast<VirtualFile>());
            return true;
        }

        connect(ptr.data(), &iFile::finishedChanged, [cb, ptr](){
            cb(ptr.dynamicCast<VirtualFile>());
        });

        connect(ptr.data(), &iFile::errorChanged, [cb, ptr](){
            cb(ptr.dynamicCast<VirtualFile>());
        });

        return true;
    }

    return false;
}

QByteArray ITelegramBot::makePrefix() const {
    return "https://api.telegram.org/bot" + token();
}

size_t ITelegramBot::sendRequest(const QSharedPointer<iRequest> &rquest, const Responce &cb) {
    if (!rquest)
        return 0;


    auto getInfoRquest = makePrefix() + rquest->makeUpload();

    auto networkReplay = QSharedPointer<QNetworkReply>(_manager->get(QNetworkRequest(QUrl::fromEncoded(getInfoRquest))));
    if (!networkReplay)
        return 0;

    auto handler = [rquest, cb, networkReplay]() {

        auto rawData = networkReplay->readAll();
        qDebug() << rawData;
        auto message = IBot::makeMesasge<TelegramUpdateAnswer>();
        message->setRawData(rawData);

        if (!message->isValid()) {
            qDebug() << "Some request is wrong: code:" << message->rawJson().value("error_code").toInt();
            qDebug() << "What: " << message->rawJson().value("description").toString();

            return;
        }

        if (cb) {
            cb(rquest, message, 0);
        }
    };

    auto err = [rquest, cb, networkReplay](QNetworkReply::NetworkError err) {

        networkReplay->deleteLater();

        if (cb) {
            cb(rquest, nullptr, err);
        }
    };

    connect(networkReplay.get(), &QNetworkReply::finished, handler);
    connect(networkReplay.get(), &QNetworkReply::errorOccurred, err);

    return true;
}

QSharedPointer<QNetworkReply> ITelegramBot::sendRequest(const QSharedPointer<iRequest> &rquest) {
    if (!rquest)
        return 0;


    auto getInfoRquest = makePrefix() + rquest->makeUpload();

    qDebug() << getInfoRquest;

    auto&& networkReplay = QSharedPointer<QNetworkReply>(_manager->get(QNetworkRequest(QUrl::fromEncoded(getInfoRquest))));
    if (!networkReplay)
        return 0;

    return std::move(networkReplay);
}

int ITelegramBot::getFileSizeByUniqueId(const QString &id) const {
    if (auto && file = _filesMetaInfo.value(id)) {
        return file->fileSize();
    }

    return 0;
}

void ITelegramBot::incomeNewMessage(const QSharedPointer<iMessage> &msg) {
    IBot::incomeNewMessage(msg);

    extractAllMetaInfoFromUpdate(msg);
}

QString ITelegramBot::findFileInlocatStorage(const QString &fileId) const {
    QDir defaultFileDir(defaultFileStorageLocation());

    auto &&localStorageList = defaultFileDir.entryInfoList(QDir::Filter::NoDotAndDotDot | QDir::Files);
    for (const auto& file: localStorageList) {
        int size = file.size();
        if (file.fileName().contains(fileId) && size && size == getFileSizeByUniqueId(fileId)) {
            return file.absoluteFilePath();
        }
    }

    return "";
}

void ITelegramBot::extractAllMetaInfoFromUpdate(const QSharedPointer<iMessage> &answer) {
    if (auto && tmessage = answer.dynamicCast<TelegramMsg>()) {
        if (tmessage->contains(tmessage->Document)) {
            auto &&doc = tmessage->documents();
            _filesMetaInfo[doc->fileId()] = doc;
        }

        if (tmessage->contains(tmessage->Image)) {
            auto &&imgs = tmessage->images();
            for (const auto& img : qAsConst(imgs)) {
                _filesMetaInfo[img->fileId()] = img;
            }
        }

        if (tmessage->contains(tmessage->Audio)) {
            auto &&audio = tmessage->image();
            _filesMetaInfo[audio->fileId()] = audio;
        }
    }
}

void ITelegramBot::setUsername(const QString &newUsername) {
    _username = newUsername;
}

void ITelegramBot::setId(unsigned long long newId) {
    _id = newId;
}

const QString &ITelegramBot::username() const {
    return _username;
}

unsigned long long ITelegramBot::id() const {
    return _id;
}

} // namespace qTbot
