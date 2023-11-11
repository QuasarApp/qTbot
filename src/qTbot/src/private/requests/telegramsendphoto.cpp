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
                                     const QByteArray &data):
    TelegramSendFile("sendPhoto", chatId, text, fileName, data) {

}

TelegramSendPhoto::TelegramSendPhoto(const QVariant &chatId,
                                     const QString &text,
                                     const QFileInfo &file):
    TelegramSendFile("sendPhoto", chatId, text, file) {


}

}
