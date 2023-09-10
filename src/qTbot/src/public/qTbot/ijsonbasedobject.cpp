//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ijsonbasedobject.h"

namespace qTbot {

IJsonBasedObject::IJsonBasedObject()
{

}

const QJsonObject &IJsonBasedMessage::rawJson() const {
    return _rawJson;
}

void IJsonBasedMessage::setRawJson(const QJsonObject &newRawJson) {
    _rawJson = newRawJson;
}

}
