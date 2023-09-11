//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramaudio.h"

namespace qTbot {

TelegramAudio::TelegramAudio()
{

}

TelegramAudio::TelegramAudio(const QJsonObject &jsonObject) : IJsonBasedObject(jsonObject) {}

int TelegramAudio::duration() const {
    return rawJson()["duration"].toInt();
}

QString TelegramAudio::fileName() const {
    return rawJson()["file_name"].toString();
}

QString TelegramAudio::mimeType() const {
    return rawJson()["mime_type"].toString();
}

QString TelegramAudio::fileId() const {
    return rawJson()["file_id"].toString();
}

QString TelegramAudio::fileUniqueId() const {
    return rawJson()["file_unique_id"].toString();
}

int TelegramAudio::fileSize() const {
    return rawJson()["file_size"].toInt();
}
}
