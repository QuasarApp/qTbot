//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMGETME_H
#define TELEGRAMGETME_H

#include "telegramsinglerquest.h"

namespace qTbot {

/**
 * @brief The TelegramGetMsg class just prepare get request to tellegram
 */
class TelegramGetMe final: public TelegramSingleRquest
{
public:
    TelegramGetMe();
};
}
#endif // TELEGRAMGETME_H
