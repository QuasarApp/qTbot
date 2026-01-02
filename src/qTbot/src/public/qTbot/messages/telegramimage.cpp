//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramimage.h"

namespace qTbot {

TelegramImage::TelegramImage()
{

}

TelegramImage::TelegramImage(const QJsonObject &jsonObject) : TelegramFile(jsonObject) {}



int TelegramImage::width() const {
    return rawJson()["width"].toInt();
}


int TelegramImage::height() const {
    return rawJson()["height"].toInt();
}

}
