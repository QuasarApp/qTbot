//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "telegramsendphoto.h"

namespace qTbot {


TelegramSendPhoto::TelegramSendPhoto(const TelegramArgs &args,
                                     const QString &fileName,
                                     const QByteArray &data,
                                     const ExtraJsonObjects &extraObjects):
    TelegramSendFile("sendPhoto", fileName, TELEGRAM_PHOTO, data, args, extraObjects) {}

TelegramSendPhoto::TelegramSendPhoto(const TelegramArgs &args,
                                     const QFileInfo &file,
                                     const ExtraJsonObjects &extraObjects):
    TelegramSendFile("sendPhoto", file, args, extraObjects){}

}
