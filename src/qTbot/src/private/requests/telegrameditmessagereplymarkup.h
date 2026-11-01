//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMEDITMESSAGEREPLYMARKUP_H
#define TELEGRAMEDITMESSAGEREPLYMARKUP_H

#include "telegrameditmessage.h"
namespace qTbot {

/**
 * @brief The TelegramEditMessageReplyMarkup class just edits the already created reply markups of a message.
 */
class TelegramEditMessageReplyMarkup: public TelegramEditMessage
{
public:
    /**
     * @brief TelegramEditMessageReplyMarkup prepares the edit reply markup request.
     * @param idEditedMessage This is the id of the message that needs to be edited.
     * @param args This is the general arguments of the request.
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramEditMessageReplyMarkup(const QVariant& idEditedMessage,
                                   const TelegramArgs &args,
                                   const ExtraJsonObjects& extraObjects = {});
};
}
#endif // TELEGRAMEDITMESSAGEREPLYMARKUP_H
