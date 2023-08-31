//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "imessage.h"

namespace qTbot {

iMessage::iMessage() {

}

const QByteArray& iMessage::rawData() const {
    return _rawData;
}

void iMessage::setRawData(const QByteArray &newRawData) {
    _rawData = newRawData;
}

const QByteArray &iMessage::userId() const {
    return _userId;
}

void iMessage::setUserId(const QByteArray &newUserId) {
    _userId = newUserId;
}

bool iMessage::isValid() const {
    return _userId.size();
}
}
