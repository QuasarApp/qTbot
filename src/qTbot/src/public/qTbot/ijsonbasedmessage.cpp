//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "ijsonbasedmessage.h"
#include "qjsondocument.h"

namespace qTbot {

IJsonBasedMessage::IJsonBasedMessage() {

}

bool IJsonBasedMessage::isValid() const {
    return !rawJson().empty();
}

void IJsonBasedMessage::setRawData(const QByteArray &newRawData) {
    iMessage::setRawData(newRawData);

    auto doc = QJsonDocument::fromJson(newRawData);
    if (!doc.isObject()) {
        return;
    }
    setRawJson(doc.object());

}
}
