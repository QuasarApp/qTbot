//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMRESTBOT_H
#define TELEGRAMRESTBOT_H

#include "itelegrambot.h"

namespace qTbot {

/**
 * @brief The TelegramRestBot class Is Rest implementation base on the Update API telegram method
 */
class QTBOT_EXPORT TelegramRestBot: public ITelegramBot
{
public:
    TelegramRestBot();

    // IBot interface
    bool login(const QByteArray &token);
    bool sendMessage(const QSharedPointer<iMessage> &message);
};
}
#endif // TELEGRAMRESTBOT_H
