//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "telegramfile.h"

namespace qTbot {

TelegramFile::TelegramFile() {

}

TelegramFile::TelegramFile(const QJsonObject &jsonObject): IJsonBasedObject(jsonObject) {

}

int TelegramFile::fileSize() const {
    return rawJson()["file_size"].toInt();
}

QString TelegramFile::path() {
    if (_used)
        return "";

    _used = true;

    return rawJson()["file_path"].toString();
}

QString TelegramFile::fileId() const {
    return rawJson()["file_id"].toString();
}


QString TelegramFile::fileUniqueId() const {
    return rawJson()["file_unique_id"].toString();
}

}
