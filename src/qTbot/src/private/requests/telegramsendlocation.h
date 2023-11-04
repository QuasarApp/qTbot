//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSENDLOCATION_H
#define TELEGRAMSENDLOCATION_H

#include "requests/telegramsinglerquest.h"
namespace qTbot {

/**
 * @brief The TelegramSendLocation class sents location data into chat
 */
class TelegramSendLocation: public TelegramSingleRquest
{
public:
    TelegramSendLocation(const QVariant &chatId,
                         const QString &text,
                         float latitude,
                         float longitude,
                         unsigned long long replyToMessageId);
};
}
#endif // TELEGRAMSENDLOCATION_H
