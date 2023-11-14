//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramsenddocument.h"

namespace qTbot {

TelegramSendDocument::TelegramSendDocument(const QVariant &chatId,
                                           const QString &text,
                                           const QString& fileName,
                                           const QByteArray &data,
                                           const QString &parseMode,
                                           unsigned long long replyToMessageId,
                                           const ExtraJsonObjects &extraObjects):
    TelegramSendFile("sendDocument", chatId, text, fileName, TELEGRAM_DOCUMENT, data, parseMode, replyToMessageId, extraObjects) {}

TelegramSendDocument::TelegramSendDocument(const QVariant &chatId,
                                           const QString &text,
                                           const QFileInfo &file,
                                           const QString &parseMode,
                                           unsigned long long replyToMessageId,
                                           const ExtraJsonObjects &extraObjects):
    TelegramSendFile("sendDocument", chatId, text, file, parseMode, replyToMessageId, extraObjects) {}

}
