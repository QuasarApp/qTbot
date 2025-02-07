//#
//# Copyright (C) 2023-2025 QuasarApp.
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
 * @brief The TelegramSendMsg class This method send a message to the server.
 */
class TelegramSendMsg: public TelegramSingleRquest
{
public:

    /**
     * @brief TelegramSendMsg This object sents msg to telegram server.
     * @param args this is generatl arguments of request (include target chat id).
     * @param extraObjects additional objects of the telegram messages (json).
     */
    TelegramSendMsg(const TelegramArgs& args,
                    const ExtraJsonObjects& extraObjects = {});
};
}
#endif // TELEGRAMSENDMSG_H
