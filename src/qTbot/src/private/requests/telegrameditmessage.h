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
 * @brief The TelegramEditMessage class This command edits the text and the keyboard of a message.
 */
class TelegramEditMessage: public TelegramSendMsg
{
public:
    /**
     * @brief TelegramEditMessage prepares the edit request.
     * @param idEditedMessage This is the id of the message that needs to be edited.
     * @param args This is the general arguments of the request.
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramEditMessage(const QVariant& idEditedMessage,
                        const TelegramArgs& args,
                        const ExtraJsonObjects& extraObjects = {});
};
}
#endif // TELEGRAMEDITMESSAGE_H
