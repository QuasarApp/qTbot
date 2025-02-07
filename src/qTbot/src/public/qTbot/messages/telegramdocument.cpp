//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramdocument.h"

namespace qTbot {

TelegramDocument::TelegramDocument()
{

}

TelegramDocument::TelegramDocument(const QJsonObject &jsonObject) : TelegramFile(jsonObject) {}

QString TelegramDocument::fileName() const {
    return rawJson()["file_name"].toString();
}

QString TelegramDocument::mimeType() const {
    return rawJson()["mime_type"].toString();
}

}
