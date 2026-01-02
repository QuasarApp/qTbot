//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QException>
#include <QNetworkReply>

#ifndef INTERNALEXCEPTION_H
#define INTERNALEXCEPTION_H


namespace qTbot {

/**
 * @brief The InternalException class contais string value to describe what happened.
 */
class InternalException: public QException
{
    // exception interface
public:
    InternalException(const QByteArray& erroString = {});

    const char *what() const noexcept override;

    // QException interface
public:
    void raise() const override;
    QException *clone() const override;

private:
    QByteArray _errText;
};
}
#endif // INTERNALEXCEPTION_H


