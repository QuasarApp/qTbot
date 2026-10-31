//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMGETME_H
#define TELEGRAMGETME_H

#include "telegramsinglerquest.h"

namespace qTbot {

/**
 * @brief The TelegramGetMe class just prepares the getMe request to telegram.
 * This request returns the basic information about the bot.
 */
class TelegramGetMe final: public TelegramSingleRquest
{
public:
    /**
     * @brief TelegramGetMe prepares the getMe request.
     */
    TelegramGetMe();
};
}
#endif // TELEGRAMGETME_H
