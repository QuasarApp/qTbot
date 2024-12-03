//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "httpexception.h"

HttpException::HttpException(QNetworkReply::NetworkError code,
                             const QByteArray &erroString) {

    if (erroString.size()) {
        _errText = erroString;
    } else {

        _errText = QByteArray("Http request fonoshed with code: ").
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
