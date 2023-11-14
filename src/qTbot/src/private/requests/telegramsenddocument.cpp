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
                                           const QByteArray &data):
    TelegramSendFile("sendDocument", chatId, text, fileName, TELEGRAM_DOCUMENT, data) {}

TelegramSendDocument::TelegramSendDocument(const QVariant &chatId,
                                           const QString &text,
                                           const QFileInfo &file):
    TelegramSendFile("sendDocument", chatId, text, file) {}

}
