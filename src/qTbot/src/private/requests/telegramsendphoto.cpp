//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "telegramsendphoto.h"

namespace qTbot {


TelegramSendPhoto::TelegramSendPhoto(const QVariant &chatId,
                                     const QString &text,
                                     const QString &fileName,
                                     const QByteArray &data,
                                     unsigned long long replyToMessageId,
                                     const QMap<QString, QSharedPointer<QJsonObject>>& extraObjects
                                     ):
    TelegramSendFile("sendPhoto", chatId, text, fileName, TELEGRAM_PHOTO, data, replyToMessageId, extraObjects) {

}

TelegramSendPhoto::TelegramSendPhoto(const QVariant &chatId,
                                     const QString &text,
                                     const QFileInfo &file,
                                     unsigned long long replyToMessageId,
                                     const QMap<QString, QSharedPointer<QJsonObject> > &extraObjects):
    TelegramSendFile("sendPhoto", chatId, text, file, replyToMessageId, extraObjects) {

}

}
