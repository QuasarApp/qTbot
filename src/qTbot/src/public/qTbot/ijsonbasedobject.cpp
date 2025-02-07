//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ijsonbasedobject.h"

namespace qTbot {

IJsonBasedObject::IJsonBasedObject()
{

}

IJsonBasedObject::IJsonBasedObject(const QJsonObject &newRawJson) {
    IJsonBasedObject::setRawJson(newRawJson);
}

const QJsonObject &IJsonBasedObject::rawJson() const {
    return _rawJson;
}

void IJsonBasedObject::setRawJson(const QJsonObject &newRawJson) {
    _rawJson = newRawJson;
}

}
