//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "ijsonbasedupdate.h"
#include "qjsondocument.h"

namespace qTbot {

IJsonBasedUpdate::IJsonBasedUpdate() {

}

bool IJsonBasedUpdate::isValid() const {
    return !rawJson().empty();
}

void IJsonBasedUpdate::setRawData(const QByteArray &newRawData) {
    iUpdate::setRawData(newRawData);

    auto doc = QJsonDocument::fromJson(newRawData);
    if (!doc.isObject()) {
        return;
    }
    setRawJson(doc.object());

}
}
