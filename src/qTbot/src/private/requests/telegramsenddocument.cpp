//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramsenddocument.h"

namespace qTbot {

TelegramSendDocument::TelegramSendDocument(const TelegramArgs &args,
                                           const QString& fileName,
                                           const QByteArray &data,
                                           const ExtraJsonObjects &extraObjects):
    TelegramSendFile("sendDocument", fileName, TELEGRAM_DOCUMENT, data, args, extraObjects) {}

TelegramSendDocument::TelegramSendDocument(const TelegramArgs &args,
                                           const QFileInfo &file,
                                           const ExtraJsonObjects &extraObjects):
    TelegramSendFile("sendDocument", file, args, extraObjects) {}

}
