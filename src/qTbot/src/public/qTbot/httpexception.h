//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QException>
#include <QNetworkReply>


#ifndef HTTPEXCEPTION_H
#define HTTPEXCEPTION_H

namespace qTbot {

/**
 * @brief The HttpException class is base exaption that will raise on all errors of the HTTP protocol,
 */
class HttpException: public QException
{
public:
    HttpException(QNetworkReply::NetworkError code, const QByteArray& erroString = {});

    // exception interface
public:
    const char *what() const noexcept override;

    // QException interface
public:
    void raise() const override;
    QException *clone() const override;

    QNetworkReply::NetworkError code() const;

private:
    QByteArray _errText;
    QNetworkReply::NetworkError _code;
};
}
#endif // HTTPEXCEPTION_H
