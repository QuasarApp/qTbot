//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMGETME_H
#define TELEGRAMGETME_H

#include "qTbot/requests/telegramsinglerquest.h"
namespace qTbot {

/**
 * @brief The TelegramGetMsg class just prepare get request to tellegram
 */
class QTBOT_EXPORT TelegramGetMe final: public TelegramSingleRquest
{
public:
    TelegramGetMe();
};
}
#endif // TELEGRAMGETME_H
