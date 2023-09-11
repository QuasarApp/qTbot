//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramdocument.h"

namespace qTbot {

TelegramDocument::TelegramDocument()
{

}

TelegramDocument::TelegramDocument(const QJsonObject &jsonObject) : IJsonBasedObject(jsonObject) {}

QString TelegramDocument::fileName() const {
    return rawJson()["file_name"].toString();
}

QString TelegramDocument::mimeType() const {
    return rawJson()["mime_type"].toString();
}

QString TelegramDocument::fileId() const {
    return rawJson()["file_id"].toString();
}

QString TelegramDocument::fileUniqueId() const {
    return rawJson()["file_unique_id"].toString();
}

int TelegramDocument::fileSize() const {
    return rawJson()["file_size"].toInt();
}

}
