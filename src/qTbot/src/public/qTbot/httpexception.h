//#
//# Copyright (C) 2023-2026 QuasarApp.
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
 * @brief The HttpException class is the base exception that is raised on all errors of the HTTP protocol.
 */
class HttpException: public QException
{
public:
    /**
     * @brief HttpException constructs the exception with an http error code and an error description.
     * @param code This is the network error code.
     * @param erroString This is the text description of the error.
     */
    HttpException(QNetworkReply::NetworkError code, const QByteArray& erroString = {});

    // exception interface
public:
    /**
     * @brief what Returns the text description of the error.
     * @return error description as a c string.
     */
    const char *what() const noexcept override;

    // QException interface
public:
    /**
     * @brief raise Raises the exception.
     */
    void raise() const override;

    /**
     * @brief clone Creates a copy of the exception.
     * @return a pointer to the new exception instance.
     */
    QException *clone() const override;

    /**
     * @brief code Returns the network error code.
     * @return the network error code.
     */
    QNetworkReply::NetworkError code() const;

private:
    QByteArray _errText;
    QNetworkReply::NetworkError _code;
};
}
#endif // HTTPEXCEPTION_H
