//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramaudio.h"

namespace qTbot {

TelegramAudio::TelegramAudio()
{

}

TelegramAudio::TelegramAudio(const QJsonObject &jsonObject) : TelegramFile(jsonObject) {}

int TelegramAudio::duration() const {
    return rawJson()["duration"].toInt();
}

QString TelegramAudio::fileName() const {
    return rawJson()["file_name"].toString();
}

QString TelegramAudio::mimeType() const {
    return rawJson()["mime_type"].toString();
}
}

