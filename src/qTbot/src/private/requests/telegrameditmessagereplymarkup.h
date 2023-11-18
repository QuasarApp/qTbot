//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMEDITMESSAGEREPLYMARKUP_H
#define TELEGRAMEDITMESSAGEREPLYMARKUP_H

#include "telegrameditmessage.h"
namespace qTbot {

/**
 * @brief The TelegramEditMessageReplyMarkup class just edit alredy created Markups.
 */
class TelegramEditMessageReplyMarkup: public TelegramEditMessage
{
public:
    TelegramEditMessageReplyMarkup(const QVariant& idEditedMessage,
                                   const TelegramArgs &args,
                                   const ExtraJsonObjects& extraObjects = {});
};
}
#endif // TELEGRAMEDITMESSAGEREPLYMARKUP_H
