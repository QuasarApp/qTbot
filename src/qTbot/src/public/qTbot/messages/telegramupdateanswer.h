//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef TELEGRAMUPDATEANSVER_H
#define TELEGRAMUPDATEANSVER_H

#include <qTbot/ijsonbasedupdate.h>

namespace qTbot {

/**
 * @brief The TelegramUpdateAnswer class This is a base message from the telegram server after an update request.
 */
class QTBOT_EXPORT TelegramUpdateAnswer: public IJsonBasedUpdate
{
public:
    /**
     * @brief TelegramUpdateAnswer default constructor.
     */
    TelegramUpdateAnswer();

    // iMessage interface
    bool isValid() const override;

    /**
     * @brief result This is the result field of the telegram response.
     * @return json value of the result field.
     */
    QJsonValue result() const;

    /**
     * @brief errorCode This is the error code (if it exists).
     * @return error code
     */
    int errorCode() const;

    /**
     * @brief errorDescription This is the text description of what happened.
     * @return text message about the error.
     */
    QString errorDescription() const;

    QString from() const override;
    QVariant chatId() const override;

    unsigned long long updateId() const override;

};

}
#endif // TELEGRAMUPDATEANSVER_H
