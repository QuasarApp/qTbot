//#
//# Copyright (C) 2018-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "itelegrambot.h"
#include "qTbot/messages/telegramupdateanswer.h"
#include "requests/telegrammdownloadfile.h"
#include "qdir.h"
#include "requests/telegramsendcontact.h"
#include "requests/telegramsenddocument.h"
#include "httpexception.h"
#include <QNetworkAccessManager>

#include <requests/telegramgetfile.h>
#include <requests/telegramgetme.h>
#include <requests/telegramsendmsg.h>
#include <requests/telegramdeletemessage.h>
#include <requests/telegrameditmessage.h>
#include <requests/telegramsendlocation.h>
#include <requests/telegramsendphoto.h>
#include <requests/telegrameditmessagereplymarkup.h>

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

    QFuture<QByteArray> loginFuture = sendRequest(QSharedPointer<TelegramGetMe>::create());
    loginFuture.
        then(this, [this](const QByteArray& data) {
                   ITelegramBot::handleLogin(data);
               } ).
        onFailed(this, [this](const HttpException& exeption){
            handleLoginErr(exeption.code());
        });
    
    return loginFuture.isValid();
}

bool ITelegramBot::sendMessage(const QVariant &chatId, const QString &text) {
    return sendSpecificMessage(TelegramArgs{chatId, text});
}

bool ITelegramBot::sendLocationRequest(const QVariant &chatId, const QString &text, const QString &buttonText,
                                       bool onetimeKeyboard) {

    auto replyMarkup = QSharedPointer<QJsonObject>::create();
    QJsonArray keyboard;
    QJsonObject contactButton;
    contactButton["text"] = buttonText;
    contactButton["request_location"] = true;
    QJsonArray row;
    row.append(contactButton);
    keyboard.append(row);
    replyMarkup->insert("keyboard", keyboard);
    replyMarkup->insert("resize_keyboard", true);
    replyMarkup->insert("one_time_keyboard", onetimeKeyboard);

    return sendSpecificMessage(TelegramArgs{chatId, text}, {{"reply_markup", replyMarkup}});
}

bool ITelegramBot::sendSelfContactRequest(const QVariant &chatId, const QString &text, const QString &buttonText,
                                          bool onetimeKeyboard) {
    auto replyMarkup = QSharedPointer<QJsonObject>::create();
    QJsonArray keyboard;
    QJsonObject contactButton;
    contactButton["text"] = buttonText;
    contactButton["request_contact"] = true;
    QJsonArray row;
    row.append(contactButton);
    keyboard.append(row);
    replyMarkup->insert("keyboard", keyboard);
    replyMarkup->insert("resize_keyboard", true);
    replyMarkup->insert("one_time_keyboard", onetimeKeyboard);

    return sendSpecificMessage(TelegramArgs{chatId, text}, {{"reply_markup", replyMarkup}});
}

bool ITelegramBot::sendSpecificMessage(const TelegramArgs& args,
                                       const ExtraJsonObjects &extraObjects) {

    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (args.text.isEmpty()) {
        return false;
    }

    auto msg = QSharedPointer<TelegramSendMsg>::create(args, extraObjects);

    return sendMessageRequest(msg, args.msgIdCB);
}

bool ITelegramBot::sendSpecificMessageWithKeyboard(const TelegramArgs& args,
                                                   const KeyboardOnMessage &keyboard) {
    return sendSpecificMessage(args, prepareInlineKeyBoard(keyboard));
}

bool ITelegramBot::deleteMessage(const QVariant &chatId, const QVariant &messageId) {
    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    auto msg = QSharedPointer<TelegramDeleteMessage>::create(chatId,
                                                             messageId);

    return sendMessageRequest(msg);
}

bool ITelegramBot::editSpecificMessageWithKeyboard(const QVariant &messageId,
                                                   const TelegramArgs& args,
                                                   const QList<QList<QString> > &keyboard,
                                                   bool onTimeKeyboard,
                                                   bool autoResizeKeyboard) {

    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    auto msg = QSharedPointer<TelegramEditMessage>::create(messageId,
                                                           args,
                                                           prepareKeyboard(autoResizeKeyboard,
                                                                           onTimeKeyboard,
                                                                           keyboard));

    return sendMessageRequest(msg, args.msgIdCB);
}

ExtraJsonObjects
qTbot::ITelegramBot::prepareInlineKeyBoard(const KeyboardOnMessage &keyboard)
{
    ExtraJsonObjects extraObjects;
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

ExtraJsonObjects
qTbot::ITelegramBot::prepareKeyboard(bool autoResizeKeyboard,
                                     bool onTimeKeyboard,
                                     const QList<QList<QString>> &keyboard) {
    ExtraJsonObjects extraObjects;
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

bool ITelegramBot::editSpecificMessageWithKeyboard(const QVariant& messageId,
                                                   const TelegramArgs& args,

                                                   const KeyboardOnMessage &keyboard ) {

    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    auto msg = QSharedPointer<TelegramEditMessage>::create(messageId,
                                                           args,
                                                           prepareInlineKeyBoard(keyboard));


    return sendMessageRequest(msg);
}

bool ITelegramBot::editMessageKeyboard(const QVariant &messageId,
                                       const QVariant &chatId,
                                       const KeyboardOnMessage &keyboard,
                                       const QString &callBackQueryId) {
    if (!chatId.isValid() || chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    auto msg = QSharedPointer<TelegramEditMessageReplyMarkup>::create(messageId,
                                                                      TelegramArgs(chatId, "", 0, "html", false, callBackQueryId),
                                                                      prepareInlineKeyBoard(keyboard));


    return sendMessageRequest(msg);
}

bool ITelegramBot::editSpecificMessage(const QVariant &messageId,
                                       const TelegramArgs& args) {

    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (!messageId.isValid() || messageId.isNull())
        return false;

    if (args.text.isEmpty())
        return false;

    auto msg = QSharedPointer<TelegramEditMessage>::create(messageId,
                                                           args
                                                           );


    return sendMessageRequest(msg);
}

bool ITelegramBot::sendSpecificMessageWithKeyboard(const TelegramArgs& args,
                                                   const QList<QList<QString> > &keyboard,
                                                   bool onTimeKeyboard,
                                                   bool autoResizeKeyboard) {

    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (args.text.isEmpty()) {
        return false;
    }

    return sendSpecificMessage(args, prepareKeyboard(autoResizeKeyboard, onTimeKeyboard, keyboard));
}

QFuture<QByteArray> ITelegramBot::getFile(const QString &fileId, FileType fileType) {


    if (fileId.isEmpty()) {
        return {};
    }

    auto localFilePath = findFileInlocatStorage(fileId);

    if (!localFilePath.isEmpty()) {
        QPromise<QByteArray> fileDataResult;

        if (fileType == FileType::Ram) {
            QFile localFile(localFilePath);
            if (localFile.open(QIODevice::ReadOnly)) {
                fileDataResult.addResult(localFile.readAll());
                localFile.close();
            }

        } else if (fileType == FileType::Local) {
            fileDataResult.addResult(localFilePath.toUtf8());
        }

        fileDataResult.setProgressRange(0,1);
        fileDataResult.setProgressValue(1);

        fileDataResult.finish();

        return fileDataResult.future();
    }

    auto&& metaInfo = getFileInfoByUniqueId(fileId);
    localFilePath = defaultFileStorageLocation() + "/" + fileId;

    if (metaInfo) {
        auto&& path = metaInfo->takePath();
        if (path.size()) {
            auto&& msg = QSharedPointer<TelegrammDownloadFile>::create(path);

            QDir().mkpath(defaultFileStorageLocation());


            if (localFilePath.isEmpty())
                return {};

            QFuture<QByteArray> replay;
            if (fileType == FileType::Ram) {
                replay = sendRequest(msg);
            } else {
                replay = sendRequest(msg, localFilePath);
            }

            return replay;
        }
    }

    auto longWay = QSharedPointer<QPromise<QByteArray>>::create();
    longWay->start();

    auto&& future = getFileMeta(fileId);
    if (!future.isValid()) {
        return {};
    }

    future.then([this, fileId, fileType, longWay](const QByteArray& header){
        handleFileHeader(header);

        getFile(fileId, fileType).then([longWay](const QByteArray& data){
            longWay->addResult(data);
        });
    });

    return longWay->future();
}

QFuture<QByteArray> ITelegramBot::getFileMeta(const QString &fileId) {
    auto msg = QSharedPointer<TelegramGetFile>::create(fileId);
    auto && future = sendRequest(msg);
    if (future.isValid()) {
        return future;
    }

    return {};
}

bool ITelegramBot::sendFile(const QFileInfo &file, const QVariant &chatId) {
    return sendFileMessage({chatId}, file);
}

bool ITelegramBot::sendFile(const QByteArray &file, const QString &fileName, const QVariant &chatId) {
    return sendFileMessage({chatId}, file, fileName);
}

bool ITelegramBot::sendFileMessage(const TelegramArgs &args, const QFileInfo &file) {
    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (!file.isReadable()) {
        return false;
    }

    return sendMessageRequest(
        QSharedPointer<TelegramSendPhoto>::create(args,
                                                  file), args.msgIdCB);
}

bool ITelegramBot::sendFileMessage(const TelegramArgs &args, const QByteArray &file, const QString &fileName) {
    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (!fileName.size()) {
        return false;
    }

    if (!file.size()) {
        return false;
    }

    return sendMessageRequest(QSharedPointer<TelegramSendDocument>::create(args, fileName, file), args.msgIdCB);
}

bool ITelegramBot::sendPhoto(const TelegramArgs &args,
                             const QFileInfo &photo,
                             const KeyboardOnMessage &keyboard) {
    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (!photo.isReadable()) {
        return false;
    }

    return sendMessageRequest(
        QSharedPointer<TelegramSendPhoto>::create(args,
                                                  photo,
                                                  prepareInlineKeyBoard(keyboard)), args.msgIdCB);
}

bool ITelegramBot::sendPhoto(const TelegramArgs &args,
                             const QByteArray &photo,
                             const QString &fileName,
                             const KeyboardOnMessage &keyboard) {

    if (!args.chatId.isValid() || args.chatId.isNull()) {
        return false;
    }

    if (!fileName.size()) {
        return false;
    }

    if (!photo.size()) {
        return false;
    }

    return sendMessageRequest(
        QSharedPointer<TelegramSendPhoto>::create(args,
                                                  fileName,
                                                  photo,
                                                  prepareInlineKeyBoard(keyboard)),
        args.msgIdCB);
}

bool ITelegramBot::sendFileById(const QString &fileID, const QVariant &chatId) {
    Q_UNUSED(fileID)
    Q_UNUSED(chatId)

    throw "the sendFileById is not implemented";

    return false;

}

bool ITelegramBot::sendLocation(const TelegramArgs &args,
                                float latitude,
                                float longitude,
                                const KeyboardOnMessage &keyboard) {

    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    if (!(longitude && latitude)) {
        return false;
    }

    return sendMessageRequest(QSharedPointer<TelegramSendLocation>::create(args,
                                                                           latitude,
                                                                           longitude,
                                                                           prepareInlineKeyBoard(keyboard)));
}

bool ITelegramBot::sendContact(const TelegramArgs &args,
                               const QString &phone,
                               const QString &firstName,
                               const QString &secondName) {
    if (!args.chatId.isValid() || args.chatId.isNull())
        return false;

    return sendMessageRequest(QSharedPointer<TelegramSendContact>::create(args,
                                                                          firstName,
                                                                          phone,
                                                                          secondName));
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

bool ITelegramBot::sendMessageRequest(const QSharedPointer<iRequest> &rquest,
                                      const std::function<void (int)> &msgIdCB) {
    auto&& future = IBot::sendRequest(rquest);
    if (future.isValid()) {
        future.then(this, [this, msgIdCB](const QByteArray& responseData){

                  QJsonDocument json = QJsonDocument::fromJson(responseData);

                  const QJsonObject&& obj = json.object();
                  if (obj.contains("result")) {
                      unsigned long long chatId = obj["result"]["chat"]["id"].toInteger();
                      int messageID = obj["result"]["message_id"].toInt();
                      if (msgIdCB) {
                          msgIdCB(messageID);
                      }

                      if (chatId) {
                          _lastMessageId[chatId] = messageID;
                      }

                      return;
                  }
              }).onFailed([msgIdCB](){

                if (msgIdCB) {
                    msgIdCB(-1);
                }
            });

        return true;
    }

    return false;
}

void ITelegramBot::handleLogin(const QByteArray&ansver) {

    auto&& ans = makeMesasge<TelegramUpdateAnswer>(ansver);

    if (!ans->isValid()) {
        qWarning() << "login error occured: ";
        return;
    }

    auto&& result = ans->result().toObject();

    setId(result.value("id").toInteger());
    setName( result.value("first_name").toString());
    setUsername( result.value("username").toString());

}

void ITelegramBot::handleLoginErr(QNetworkReply::NetworkError err) {
    if (err) {
        qCritical() << "Network error occured. code: " << err;
    }
}

void ITelegramBot::handleFileHeader(const QByteArray& header) {
    auto&& ansver = makeMesasge<TelegramUpdateAnswer>(header);

    if (!ansver->isValid()) {
        onRequestError(ansver);
        return;
    }

    auto &&fileMetaInfo = makeMesasge<TelegramFile>(ansver->result().toObject());

    _filesMetaInfo.insert(fileMetaInfo->fileId(), fileMetaInfo);
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

int ITelegramBot::gelLastMessageId(unsigned long long &chatId) const {
    return _lastMessageId.value(chatId, 0);
}

unsigned long long ITelegramBot::id() const {
    return _id;
}

} // namespace qTbot
