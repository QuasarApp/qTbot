//#
//# Copyright (C) 2023-2026 QuasarApp.
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
 * @brief The TelegramSendContact class prepares the sendContact request that sends a contact into the chat.
 */
class TelegramSendContact: public TelegramSingleRquest
{
public:

    /**
     * @brief TelegramSendContact prepares the send contact request.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param firstName This is the first name of the contact.
     * @param phone This is the phone number of the contact.
     * @param lastName This is the last name of the contact.
     */
    TelegramSendContact(const TelegramArgs &args,
                        const QString &firstName,
                        const QString &phone,
                        const QString &lastName);
};
}
#endif // TELEGRAMSENDCONTACT_H
