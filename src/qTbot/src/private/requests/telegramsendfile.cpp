//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramsendfile.h"

#include <QJsonDocument>

namespace qTbot {


qTbot::TelegramSendFile::TelegramSendFile(const QString &request,
                                          const QVariant &chatId,
                                          const QString &text,
                                          const QString &fileName,
                                          const QString &fileType,
                                          const QByteArray &data,
                                          const QString& parseMode,
                                          unsigned long long replyToMessageId,
                                          const ExtraJsonObjects& extraObjects
                                          ):
    TelegramSingleRquest(request) {

    addArg("chat_id", chatId);
    if (text.size())
        addArg("caption", text);

    if (replyToMessageId > 0) {
        addArg("reply_to_message_id", replyToMessageId);
    }

    if (parseMode.size()) {
        addArg("parse_mode", parseMode);
    }

    for (auto it = extraObjects.begin(); it != extraObjects.end(); it = std::next(it)) {
        addArg(it.key(), QJsonDocument(*it.value()).toJson(QJsonDocument::Compact));
    }

    addArg(QString("%0:%1:%2").arg(REQUEST_UPLOAD_FILE_KEY, fileName, fileType), data);
}

qTbot::TelegramSendFile::TelegramSendFile(const QString &request,
                                          const QVariant &chatId,
                                          const QString &text,
                                          const QFileInfo &file,
                                          const QString &parseMode,
                                          unsigned long long replyToMessageId,
                                          const QHash<QString, QSharedPointer<QJsonObject> > &extraObjects):
    TelegramSingleRquest(request) {

    addArg("chat_id", chatId);

    if (text.size())
        addArg("text", text);

    if (replyToMessageId > 0) {
        addArg("reply_to_message_id", replyToMessageId);
    }

    if (parseMode.size()) {
        addArg("parse_mode", parseMode);
    }

    QFile readFile(file.absoluteFilePath());
    if (!readFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Fail to open file" << file.absoluteFilePath();
    }

    for (auto it = extraObjects.begin(); it != extraObjects.end(); it = std::next(it)) {
        addArg(it.key(), QJsonDocument(*it.value()).toJson(QJsonDocument::Compact));
    }

    auto&& sufix = file.suffix();
    if (sufix.contains("png") || sufix.contains("jpg") || sufix.contains("jepg") || sufix.contains("gif")) {
        addArg(QString("%0:%1:%2").arg(REQUEST_UPLOAD_FILE_KEY, file.fileName(), TELEGRAM_PHOTO),  readFile.readAll());

    } else {
        addArg(QString("%0:%1:%2").arg(REQUEST_UPLOAD_FILE_KEY, file.fileName(), TELEGRAM_DOCUMENT), readFile.readAll());

    }

    readFile.close();
}

iRequest::RequestMethod TelegramSendFile::method() const {
    return iRequest::RequestMethod::Upload;
}

QString TelegramSendFile::type() const {
    return REQUEST_UPLOAD_FILE_KEY;
}
}
