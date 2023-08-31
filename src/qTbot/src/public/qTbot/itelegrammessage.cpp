//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "itelegrammessage.h"
namespace qTbot {

ItelegramMessage::ItelegramMessage()
{

}

QByteArray ItelegramMessage::makeUpload() const {

}

const QJsonObject &ItelegramMessage::rawJson() const {
    return _rawJson;
}

void ItelegramMessage::setRawJson(const QJsonObject &newRawJson) {
    _rawJson = newRawJson;
}
}
