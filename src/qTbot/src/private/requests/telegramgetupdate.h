//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#




#ifndef TELEGRAMGETUPDATE_H
#define TELEGRAMGETUPDATE_H
#include "telegramsinglerquest.h"

namespace qTbot {

/**
 * @brief The TelegramGetUpdate class This is implementation of the get update method of the Telegram API
 */
class TelegramGetUpdate final: public TelegramSingleRquest
{
public:
    /**
     * @brief TelegramGetUpdate sends a request for updates. You will get the response immediately or after 60 seconds if the bot does not have any updates.
     * @param offset - the last accepted update id.
     */
    TelegramGetUpdate(unsigned long long offset = 0);
};
}
#endif // TELEGRAMGETUPDATE_H
