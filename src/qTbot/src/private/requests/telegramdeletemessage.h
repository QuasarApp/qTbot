//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMDELETEMESSAGE_H
#define TELEGRAMDELETEMESSAGE_H

#include "requests/telegramsinglerquest.h"
namespace qTbot {

/**
 * @brief The TelegramDeleteMessage class prepares the deleteMessage request to remove a message with the selected id.
 */
class TelegramDeleteMessage: public TelegramSingleRquest
{
public:
    /**
     * @brief TelegramDeleteMessage prepares the delete request.
     * @param chatId This is the id of the chat where the message is located.
     * @param messageId This is the id of the message that needs to be removed.
     */
    TelegramDeleteMessage(const QVariant& chatId,
                          const QVariant& messageId);
};

}
#endif // TELEGRAMDELETEMESSAGE_H
