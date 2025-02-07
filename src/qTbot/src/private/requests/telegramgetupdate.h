//#
//# Copyright (C) 2023-2025 QuasarApp.
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
     * @brief TelegramGetUpdate send request for updates. You will get response on immediacy or after 60 seconds if bot does not have any updates.
     * @param offset - last accepted update id.
     */
    TelegramGetUpdate(unsigned long long offset = 0);
};
}
#endif // TELEGRAMGETUPDATE_H
