//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMGETMSG_H
#define TELEGRAMGETMSG_H

#include "qTbot/messages/telegramsinglerquest.h"
namespace qTbot {

/**
 * @brief The TelegramGetMsg class just prepare get request to tellegram
 */
class QTBOT_EXPORT TelegramGetMsg final: public TelegramSingleRquest
{
public:
    TelegramGetMsg();
};
}
#endif // TELEGRAMGETMSG_H