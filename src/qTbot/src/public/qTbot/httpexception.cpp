//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "httpexception.h"

namespace qTbot {

HttpException::HttpException(QNetworkReply::NetworkError code,
                             const QByteArray &erroString) {

    _code = code;

    if (erroString.size()) {
        _errText = erroString;
    } else {

        _errText = QByteArray("Http request finished with code: ").
                   append(QString::number(code).toLatin1());
    }
}

const char *HttpException::what() const noexcept {
    return _errText.constData();
}

void HttpException::raise() const {
    throw *this;
}

QException *HttpException::clone() const {
    return new HttpException(QNetworkReply::NetworkError(0),
                             _errText);
}

QNetworkReply::NetworkError HttpException::code() const {
    return _code;
}
}
