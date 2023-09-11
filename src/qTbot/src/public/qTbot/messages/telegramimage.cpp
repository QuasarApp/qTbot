//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramimage.h"

namespace qTbot {

TelegramImage::TelegramImage()
{

}

TelegramImage::TelegramImage(const QJsonObject &jsonObject) : IJsonBasedObject(jsonObject) {}


QString TelegramImage::fileId() const {
    return rawJson()["file_id"].toString();
}


QString TelegramImage::fileUniqueId() const {
    return rawJson()["file_unique_id"].toString();
}


int TelegramImage::fileSize() const {
    return rawJson()["file_size"].toInt();
}


int TelegramImage::width() const {
    return rawJson()["width"].toInt();
}


int TelegramImage::height() const {
    return rawJson()["height"].toInt();
}

}
