//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSENDLOCATION_H
#define TELEGRAMSENDLOCATION_H

#include "qTbot/telegramargs.h"
#include "requests/telegramsinglerquest.h"
namespace qTbot {

/**
 * @brief The TelegramSendLocation class sents location data into chat
 */
class TelegramSendLocation: public TelegramSingleRquest
{
public:
    TelegramSendLocation(const TelegramArgs &args,
                         float latitude,
                         float longitude,
                         const ExtraJsonObjects& extraObjects = {});
};
}
#endif // TELEGRAMSENDLOCATION_H
