//#
//# Copyright (C) 2018-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "itelegrambot.h"
#include "qTbot/messages/telegramupdateanswer.h"
#include "file.h"
#include "requests/telegrammdownloadfile.h"
#include "qdir.h"
#include "requests/telegramsenddocument.h"
#include "virtualfile.h"
#include <QNetworkAccessManager>

#include <requests/telegramgetfile.h>
#include <requests/telegramgetme.h>
#include <requests/telegramsendmsg.h>
#include <requests/telegramdeletemessage.h>
#include <requests/telegrameditmessage.h>
#include <requests/telegramsendlocation.h>
#include <requests/telegramsendphoto.h>

#include <QNetworkReply>
#include <QSharedPointer>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <qTbot/messages/telegramfile.h>
#include <qTbot/messages/telegramfile.h>
#include <qTbot/messages/telegramupdate.h>


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
                                       const QMap<QString, QSharedPointer<QJsonObject>> &extraObjects,
                                       const QString &callBackQueryId,
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
                                                       extraObjects,
                                                       replyToMessageId,
                                                       markdown,
                                                       callBackQueryId,
                                                       disableWebPagePreview);

    return bool(sendRequest(msg));
}

bool ITelegramBot::sendSpecificMessageWithKeyboard(const QVariant &chatId,
                                                   const QString &text,
                                                   const QList<QList<QString>> &keyboard,
                                                   const QString &callBackQueryId,
                                                   bool onTimeKeyboard,
                                                   bool autoResizeKeyboard,
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
                                                       prepareKeyboard(autoResizeKeyboard, onTimeKeyboard, keyboard),
                                                       replyToMessageId,
                                                       markdown,
                                                       callBackQueryId,
                                                       disableWebPagePreview);

    return bool(sendRequest(msg));
}

bool ITelegramBot::deleteMessage(const QVariant &chatId, const QVariant &messageId) {
    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    auto msg = QSharedPointer<TelegramDeleteMessage>::create(chatId,
                                                             messageId);

    return bool(sendRequest(msg));
}

bool ITelegramBot::editSpecificMessageWithKeyboard(const QVariant & messageId,
                                                   const QVariant &chatId,
                                                   const QString &newText,
                                                   bool markdown,
                                                   bool disableWebPagePreview,
                                                   const QList<QList<QString>> &keyboard,
                                                   const QString &callBackQueryId,
                                                   bool onTimeKeyboard,
                                                   bool autoResizeKeyboard) {

    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    auto msg = QSharedPointer<TelegramEditMessage>::create(messageId,
                                                           chatId,
                                                           newText,
                                                           markdown,
                                                           disableWebPagePreview,
                                                           callBackQueryId,
                                                           prepareKeyboard(autoResizeKeyboard,
                                                                           onTimeKeyboard,
                                                                           keyboard));

    return bool(sendRequest(msg));
}

QMap<QString, QSharedPointer<QJsonObject>>
qTbot::ITelegramBot::prepareInlineKeyBoard(const QList<QMap<QString, std::function<void (const QString &, const QVariant &)> > > &keyboard)
{
    QMap<QString, QSharedPointer<QJsonObject>> extraObjects;
    auto&& keyboardJson = QSharedPointer<QJsonObject>::create();
    QJsonArray keyboardArray;

    for (const auto& map : keyboard) {
        QJsonArray keyboardLineArray;
        for (auto it = map.begin(); it != map.end(); it = std::next(it)) {
            auto&& callBackKey = QString("callback_data_%0").arg(rand());
            keyboardLineArray.push_back(QJsonObject{ {"text", it.key()}, {"callback_data", callBackKey } });
            _handleButtons[callBackKey] = {it.value()};
        }
        keyboardArray.push_back(keyboardLineArray);
    }


    (*keyboardJson)["inline_keyboard"] = keyboardArray;

    extraObjects["reply_markup"] = keyboardJson;

    return extraObjects;
}

QMap<QString, QSharedPointer<QJsonObject>>
qTbot::ITelegramBot::prepareKeyboard(bool autoResizeKeyboard,
                                     bool onTimeKeyboard,
                                     const QList<QList<QString>> &keyboard) {
    QMap<QString, QSharedPointer<QJsonObject>> extraObjects;
    auto&& keyboardJson = QSharedPointer<QJsonObject>::create();
    QJsonArray keyboardArray;

    for (const auto &row :keyboard) {
        QJsonArray keyboardLineArray;

        for (auto it = row.begin(); it != row.end(); it = std::next(it)) {
            keyboardLineArray.push_back(QJsonObject{ {"text", *it} });
        }
        keyboardArray.push_back(keyboardLineArray);

    }

    (*keyboardJson)["keyboard"] = keyboardArray;

    (*keyboardJson)["resize_keyboard"] = autoResizeKeyboard;
    (*keyboardJson)["one_time_keyboard"] = onTimeKeyboard;

    extraObjects["reply_markup"] = keyboardJson;

    return extraObjects;
}

bool ITelegramBot::editSpecificMessageWithKeyboard(const QVariant &messageId,
                                                   const QVariant &chatId,
                                                   const QString &text,
                                                   bool markdown,
                                                   bool disableWebPagePreview,
                                                   const QList<QMap<QString, std::function<void (const QString &, const QVariant&)> > > &keyboard,
                                                   const QString &callBackQueryId) {

    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    auto msg = QSharedPointer<TelegramEditMessage>::create(messageId,
                                                           chatId,
                                                           text,
                                                           markdown,
                                                           disableWebPagePreview,
                                                           callBackQueryId,
                                                           prepareInlineKeyBoard(keyboard));


    return bool(sendRequest(msg));
}

bool ITelegramBot::editSpecificMessage(const QVariant &messageId,
                                       const QVariant &chatId,
                                       const QString& newText,
                                       const QString &callBackQueryId,
                                       bool markdown,
                                       bool disableWebPagePreview) {

    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    if (newText.isEmpty())
        return false;

    auto msg = QSharedPointer<TelegramEditMessage>::create(messageId,
                                                           chatId,
                                                           newText,
                                                           markdown,
                                                           disableWebPagePreview,
                                                           callBackQueryId
                                                           );


    return bool(sendRequest(msg));
}

bool ITelegramBot::sendSpecificMessageWithKeyboard(const QVariant &chatId,
                                                   const QString &text,
                                                   const KeyboardOnMessage &keyboard,
                                                   const QString &callBackQueryId,
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
                                                       prepareInlineKeyBoard(keyboard),
                                                       replyToMessageId,
                                                       markdown,
                                                       callBackQueryId,
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
    localFilePath = defaultFileStorageLocation() + "/" + fileId;

    if (metaInfo) {
        auto&& path = metaInfo->takePath();
        if (path.size()) {
            auto&& msg = QSharedPointer<TelegrammDownloadFile>::create(path);

            QDir().mkpath(defaultFileStorageLocation());


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
    }


    if (fileType == iFile::Ram) {
        result = QSharedPointer<VirtualFile>::create();
    } else if (fileType == iFile::Local) {
        result = QSharedPointer<File>::create(localFilePath);
    }

    auto&& metaReploay = getFileMeta(fileId, result.toWeakRef());
    return result;
}

QSharedPointer<QNetworkReply> ITelegramBot::getFileMeta(const QString &fileId, const QWeakPointer<iFile>& receiver) {
    auto msg = QSharedPointer<TelegramGetFile>::create(fileId);

    if (auto&& ptr = sendRequest(msg)) {
        connect(ptr.get(), &QNetworkReply::finished,
                this, std::bind(&ITelegramBot::handleFileHeader, this, ptr.toWeakRef(), receiver));

        return ptr;
    }

    return nullptr;
}

bool ITelegramBot::sendFile(const QFileInfo &file, const QVariant &chatId) {
    return sendFileWithDescription(file, chatId, "");
}

bool ITelegramBot::sendFile(const QByteArray &file, const QString &fileName, const QVariant &chatId) {
    return sendFileWithDescription(file, fileName, chatId, "");
}

bool ITelegramBot::sendPhoto(const QFileInfo &photo,
                             const QVariant &chatId,
                             const QString &description) {
    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!photo.isReadable()) {
        return false;
    }

    return sendFileWithPrivate(QSharedPointer<TelegramSendPhoto>::create(chatId, description, photo));
}

bool ITelegramBot::sendPhoto(const QByteArray &photo,
                             const QString &fileName,
                             const QVariant &chatId,
                             const QString &description) {

    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!fileName.size()) {
        return false;
    }

    if (!photo.size()) {
        return false;
    }

    return sendFileWithPrivate(QSharedPointer<TelegramSendPhoto>::create(chatId, description, fileName, photo));
}

bool ITelegramBot::sendFileWithDescription(const QByteArray &file,
                                           const QString &fileName,
                                           const QVariant &chatId,
                                           const QString &description) {

    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!fileName.size()) {
        return false;
    }

    if (!file.size()) {
        return false;
    }

    return sendFileWithPrivate(QSharedPointer<TelegramSendDocument>::create(chatId, description, fileName, file));
}

bool ITelegramBot::sendFileWithDescription(const QFileInfo &file,
                                           const QVariant &chatId,
                                           const QString &description) {
    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!file.isReadable()) {
        return false;
    }

    return sendFileWithPrivate(QSharedPointer<TelegramSendDocument>::create(chatId, description, file));
}

bool ITelegramBot::sendFileById(const QString &fileID, const QVariant &chatId) {
    Q_UNUSED(fileID)
    Q_UNUSED(chatId)

    throw "the sendFileById is not implemented";

    return false;

}

bool ITelegramBot::sendLocation(const QVariant &chatId,
                                const QString &text,
                                float latitude,
                                float longitude,
                                unsigned long long replyToMessageId) {
    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!(longitude && latitude)) {
        return false;
    }

    auto&& request = QSharedPointer<TelegramSendLocation>::create(chatId, text, latitude, longitude, replyToMessageId);

    return bool(sendRequest(request));
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

void ITelegramBot::onRequestError(const QSharedPointer<TelegramUpdateAnswer> &ansverWithError) const {
    qWarning() << QString("code: %0 - %1").
                  arg(ansverWithError->errorCode()).
                  arg(ansverWithError->errorDescription());
}

void ITelegramBot::handleIncomeNewUpdate(const QSharedPointer<iUpdate> & update) {
    IBot::handleIncomeNewUpdate(update);


    if (auto&& tupdate = update.dynamicCast<TelegramUpdate>()) {

        if (auto&& queryUpd = tupdate->callbackQueryUpdate()) {
            auto &&handleButtonKey = queryUpd->callBackData();

            if (auto&& cb = _handleButtons.value(handleButtonKey)) {
                cb(handleButtonKey, queryUpd->messageId());
            }
        }
    }
}

void ITelegramBot::handleLogin() {

    if (_loginReplay) {
        auto&& ans = makeMesasge<TelegramUpdateAnswer>(_loginReplay->readAll());

        if (!ans->isValid()) {
            qWarning() << "login error occured: ";
        }

        auto&& result = ans->result().toObject();

        setId(result.value("id").toInteger());
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

void ITelegramBot::handleFileHeader(const QWeakPointer<QNetworkReply> &sender,
                                    const QWeakPointer<iFile>& receiver) {
    if (auto&& sharedPtr = sender.lock()) {
        auto&& ansver = makeMesasge<TelegramUpdateAnswer>(sharedPtr->readAll());

        if (!ansver->isValid()) {
            onRequestError(ansver);
            return;
        }

        auto &&fileMetaInfo = makeMesasge<TelegramFile>(ansver->result().toObject());

        _filesMetaInfo.insert(fileMetaInfo->fileId(), fileMetaInfo);

        if (auto&& sharedPtr = receiver.lock()) {
            auto&& downloadRequest = QSharedPointer<TelegrammDownloadFile>::create(fileMetaInfo->takePath());
            sharedPtr->setDownloadRequest(sendRequest(downloadRequest));
        }
    }
}

bool ITelegramBot::sendFileWithPrivate(const QSharedPointer<TelegramSendFile> &file) {
    return bool(sendRequest(file));
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

QString ITelegramBot::makeUrl(const QSharedPointer<iRequest> &request) const {
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
