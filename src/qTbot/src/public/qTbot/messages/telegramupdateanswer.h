//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef TELEGRAMUPDATEANSVER_H
#define TELEGRAMUPDATEANSVER_H

#include <qTbot/ijsonbasedupdate.h>

namespace qTbot {

/**
 * @brief The TelegramUpdateAnswer class This is base message from the telegram server after update request.
 */
class QTBOT_EXPORT TelegramUpdateAnswer: public IJsonBasedUpdate
{
public:
    TelegramUpdateAnswer();

    // iMessage interface
    bool isValid() const override;

    /**
     * @brief result This is result filed of thetelegram responce.
     * @return json value of the resul field.
     */
    QJsonValue result() const;

    /**
     * @brief errorCode This is error code (if exist)
     * @return error code
     */
    int errorCode() const;

    /**
     * @brief errorDescription This is text description : what is happend.
     * @return text message about error.
     */
    QString errorDescription() const;

    QString from() const override;
    QVariant chatId() const override;

    unsigned long long updateId() const override;

};

}
#endif // TELEGRAMUPDATEANSVER_H
