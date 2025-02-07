//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramlocation.h"
#include "qpoint.h"

namespace qTbot {

TelegramLocation::TelegramLocation()
{

}

TelegramLocation::TelegramLocation(const QJsonObject &jsonObject):
    IJsonBasedObject(jsonObject)  {

}

double TelegramLocation::latitude() const {
    return rawJson()["latitude"].toDouble();

}

double TelegramLocation::longitude() const {
    return rawJson()["longitude"].toDouble();

}

QPointF TelegramLocation::toQPoint() const {
    return QPointF(latitude(), longitude());
}
}
