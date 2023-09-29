//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ijsonbasedobject.h"

namespace qTbot {

bool isInteger(const QVariant &variant)
{
    switch (variant.userType())
    {
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
        return true;
    }

    return false;
}

IJsonBasedObject::IJsonBasedObject()
{

}

IJsonBasedObject::IJsonBasedObject(const QJsonObject &newRawJson) {
    IJsonBasedObject::setRawJson(newRawJson);
}

IJsonBasedObject::IJsonBasedObject(const QJsonObject &newRawJson, const QList<QVariant> &arrayAddress) {
    IJsonBasedObject::setRawJson(newRawJson);
    IJsonBasedObject::setArrayAddress(arrayAddress);

}

const QSharedPointer<const QJsonObject> &IJsonBasedObject::rawJson() const {
    return _rawJson;
}

void IJsonBasedObject::setRawJson(const QJsonObject &newRawJson) {
    _rawJson = QSharedPointer<const QJsonObject>::create(newRawJson);
}

const QList<QVariant>& IJsonBasedObject::arrayAddress() const {
    return _arrayAddress;
}

void IJsonBasedObject::setArrayAddress(const QList<QVariant> &newArrayAddress) {
    if (_arrayAddress.size() && _arrayAddress.first().userType() != QMetaType::QString ) {
        qWarning() << "You try to set a invalid address of specific json address";
        return;
    }

    _arrayAddress = newArrayAddress;
}

QJsonValue IJsonBasedObject::addressRef() const {

    if (!_arrayAddress.size()) {
        return *_rawJson;
    }

    QJsonValue result;
    for (const auto& val: _arrayAddress) {
        result = _rawJson->operator[](val.toString());

    }
}

}
