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
 * @brief The TelegramSendLocation class sends location data into the chat.
 */
class TelegramSendLocation: public TelegramSingleRquest
{
public:
    /**
     * @brief TelegramSendLocation prepares the send location request.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param latitude This is the latitude of the location.
     * @param longitude This is the longitude of the location.
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramSendLocation(const TelegramArgs &args,
                         float latitude,
                         float longitude,
                         const ExtraJsonObjects& extraObjects = {});
};
}
#endif // TELEGRAMSENDLOCATION_H
