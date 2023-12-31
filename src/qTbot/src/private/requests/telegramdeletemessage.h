//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMDELETEMESSAGE_H
#define TELEGRAMDELETEMESSAGE_H

#include "requests/telegramsinglerquest.h"
namespace qTbot {

/**
 * @brief The TelegramDeleteMessage class remove message with id.
 */
class TelegramDeleteMessage: public TelegramSingleRquest
{
public:
    TelegramDeleteMessage(const QVariant& chatId,
                          const QVariant& messageId);
};

}
#endif // TELEGRAMDELETEMESSAGE_H
