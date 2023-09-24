//#
//# Copyright (C) 2018-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "itelegrambot.h"
#include "qTbot/messages/telegrammsg.h"
#include "qTbot/messages/telegramupdateanswer.h"
#include "file.h"
#include "qTbot/requests/telegrammdownloadfile.h"
#include "qdir.h"
#include "virtualfile.h"
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
}

ITelegramBot::~ITelegramBot() {
}

bool ITelegramBot::login(const QByteArray &token) {
    if (token.isEmpty()) {
        return false;
    }

    setToken(token);

    _loginReplay = sendRequest(QSharedPointer<TelegramGetMe>::create());
    if (_loginReplay) {
        connect(_loginReplay.get(), &QNetworkReply::finished,
                this, &ITelegramBot::handleLogin,
                Qt::DirectConnection);
        connect(_loginReplay.get(), &QNetworkReply::errorOccurred,
                this, &ITelegramBot::handleLoginErr,
                Qt::DirectConnection);
        return true;
    }
    
    return false;
}

bool ITelegramBot::sendMessage(const QVariant &chatId, const QString &text) {
    return sendSpecificMessage(chatId.toLongLong(), text);
}

bool ITelegramBot::sendSpecificMessage(const QVariant & chatId,
                                       const QString &text,
                                       unsigned long long replyToMessageId,
                                       bool markdown,
                                       bool disableWebPagePreview) {

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

    return bool(sendRequest(msg));
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

    auto&& metaInfo = getFileInfoByUniqueId(fileId);
    if (!metaInfo) {
//        if (auto&& replay = getFileMeta(fileId)) {

//        } else {
//            return nullptr;
//        };
    }

    auto msg = QSharedPointer<TelegrammDownloadFile>::create(metaInfo->path());

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

QSharedPointer<QNetworkReply> ITelegramBot::getFileMeta(const QString &fileId) {
    auto msg = QSharedPointer<TelegramGetFile>::create(fileId);
    return sendRequest(msg);
}

int ITelegramBot::getFileSizeByUniqueId(const QString &id) const {
    if (auto && file = _filesMetaInfo.value(id)) {
        return file->fileSize();
    }

    return 0;
}

QSharedPointer<TelegramFile> ITelegramBot::getFileInfoByUniqueId(const QString &id) const {
    return _filesMetaInfo.value(id, nullptr);
}

void ITelegramBot::handleLogin() {

    if (_loginReplay) {
        auto&& ans = makeMesasge<TelegramUpdateAnswer>(_loginReplay->readAll());

        if (!ans->isValid()) {
            qWarning() << "login error occured: ";
        }

        auto&& result = ans->result().toObject();

        setId(result.value("id").toInt());
        setName( result.value("first_name").toString());
        setUsername( result.value("username").toString());

        _loginReplay.reset();
    }

}

void ITelegramBot::handleLoginErr(QNetworkReply::NetworkError err) {
    if (err) {
        qDebug() << "Network error occured. code: " << err;
    }
    _loginReplay.reset();
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

void ITelegramBot::setUsername(const QString &newUsername) {
    _username = newUsername;
}

QByteArray ITelegramBot::makeUrl(const QSharedPointer<iRequest> &request) const {
    return request->baseAddress() + "/bot" + token() + request->makeUpload();
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
