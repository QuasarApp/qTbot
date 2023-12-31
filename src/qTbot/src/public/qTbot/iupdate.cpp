//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "iupdate.h"

namespace qTbot {

iUpdate::iUpdate() {

}

const QByteArray& iUpdate::rawData() const {
    return _rawData;
}

void iUpdate::setRawData(const QByteArray &newRawData) {
    _rawData = newRawData;
}

bool iUpdate::isValid() const {
    return _rawData.size();
}

}
