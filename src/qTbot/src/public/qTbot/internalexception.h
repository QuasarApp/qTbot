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
 * @brief The InternalException class contains a string value to describe what happened.
 */
class InternalException: public QException
{
    // exception interface
public:
    /**
     * @brief InternalException constructs the exception with an error description.
     * @param erroString This is the text description of the error.
     */
    InternalException(const QByteArray& erroString = {});

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

private:
    QByteArray _errText;
};
}
#endif // INTERNALEXCEPTION_H


