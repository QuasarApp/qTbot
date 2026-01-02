//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMEDITMESSAGE_H
#define TELEGRAMEDITMESSAGE_H

#include "telegramsendmsg.h"
namespace qTbot {

/**
 * @brief The TelegramEditMessage class This command edit keyboard of the message.
 */
class TelegramEditMessage: public TelegramSendMsg
{
public:
    TelegramEditMessage(const QVariant& idEditedMessage,
                        const TelegramArgs& args,
                        const ExtraJsonObjects& extraObjects = {});
};
}
#endif // TELEGRAMEDITMESSAGE_H
