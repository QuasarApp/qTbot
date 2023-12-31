//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef TELEGRAMSENDCONTACT_H
#define TELEGRAMSENDCONTACT_H

#include "qTbot/telegramargs.h"
#include "telegramsinglerquest.h"

namespace qTbot {

/**
 * @brief The TelegramSendContact class
 */
class TelegramSendContact: public TelegramSingleRquest
{
public:

    TelegramSendContact(const TelegramArgs &args,
                        const QString &firstName,
                        const QString &phone,
                        const QString &lastName);
};
}
#endif // TELEGRAMSENDCONTACT_H
