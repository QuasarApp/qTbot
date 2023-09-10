//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef ITELEGRAMMESSAGE_H
#define ITELEGRAMMESSAGE_H

#include "qTbot/ijsonbasedmessage.h"

namespace qTbot {

/**
 * @brief The ItelegramMessage class This is base interface of the all telegram messages.
 */
class QTBOT_EXPORT ITelegramMessage: public IJsonBasedMessage
{
public:
    ITelegramMessage();


};

}
#endif // ITELEGRAMMESSAGE_H
