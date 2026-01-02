//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "internalexception.h"
namespace qTbot {


InternalException::InternalException(const QByteArray &erroString) {
    _errText = erroString;

}

const char *InternalException::what() const noexcept {
    return _errText.constData();
}

void InternalException::raise() const {
    throw *this;
}

QException *InternalException::clone() const {
    return new InternalException(_errText);
}
}
