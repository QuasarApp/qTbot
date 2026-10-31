//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSENDMSG_H
#define TELEGRAMSENDMSG_H

#include "qTbot/telegramargs.h"
#include "telegramsinglerquest.h"
namespace qTbot {

/**
 * @brief The TelegramSendMsg class This method sends a message to the server.
 */
class TelegramSendMsg: public TelegramSingleRquest
{
public:

    /**
     * @brief TelegramSendMsg This object sends a message to the telegram server.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param extraObjects additional objects of the telegram messages (json).
     */
    TelegramSendMsg(const TelegramArgs& args,
                    const ExtraJsonObjects& extraObjects = {});
};
}
#endif // TELEGRAMSENDMSG_H
