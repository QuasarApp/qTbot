//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "itelegrammessage.h"
#include <QJsonDocument>

namespace qTbot {

ITelegramMessage::ITelegramMessage():iMessage(){}

QByteArray ITelegramMessage::makeUpload() const {
    return QJsonDocument(_rawJson).toJson(QJsonDocument::Compact);
}

const QJsonObject &ITelegramMessage::rawJson() const {
    return _rawJson;
}

void ITelegramMessage::setRawJson(const QJsonObject &newRawJson) {
    _rawJson = newRawJson;
}

void ITelegramMessage::setRawData(const QByteArray &newRawData) {
    iMessage::setRawData(newRawData);

    auto doc = QJsonDocument::fromJson(newRawData);
    if (!doc.isObject()) {
        return;
    }
    setRawJson(doc.object());

}

bool ITelegramMessage::isValid() const {
    return _rawJson.value("ok").toBool();
}

}
