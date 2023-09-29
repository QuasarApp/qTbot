//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSENDMSG_H
#define TELEGRAMSENDMSG_H

#include "telegramsinglerquest.h"
namespace qTbot {

/**
 * @brief The TelegramSendMsg class This method send a message to the server.
 */
class TelegramSendMsg: public TelegramSingleRquest
{
public:
    TelegramSendMsg(const QVariant& chatId,
                    const QString& text,
                    unsigned long long replyToMessageId = 0,
                    bool markdown = true,
                    bool disableWebPagePreview = false);
};
}
#endif // TELEGRAMSENDMSG_H
