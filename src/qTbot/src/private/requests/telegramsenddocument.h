//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSENDDOCUMENT_H
#define TELEGRAMSENDDOCUMENT_H

#include "telegramsinglerquest.h"

namespace qTbot {

/**
 * @brief The TelegramSendDocument class sents document into chat
 */
class TelegramSendDocument: public TelegramSingleRquest
{
public:
    TelegramSendDocument();
};
}
#endif // TELEGRAMSENDDOCUMENT_H
