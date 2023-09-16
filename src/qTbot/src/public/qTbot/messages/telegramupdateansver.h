//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMUPDATEANSVER_H
#define TELEGRAMUPDATEANSVER_H

#include "itelegrammessage.h"

namespace qTbot {

/**
 * @brief The TelegramUpdateAnsver class This is base message from the telegram server after update request.
 */
class TelegramUpdateAnsver: public ITelegramMessage
{
public:
    TelegramUpdateAnsver();

    // iMessage interface
    bool isValid() const override;

    /**
     * @brief result This is result filed of thetelegram responce.
     * @return json value of the resul field.
     */
    QJsonValue result() const;

    QString from() const override;
    QVariant chatId() const override;

    unsigned long long messageId() const override;

};

}
#endif // TELEGRAMUPDATEANSVER_H
