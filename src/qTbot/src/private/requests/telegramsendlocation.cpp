//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramsendlocation.h"
namespace qTbot {

TelegramSendLocation::TelegramSendLocation(const QVariant &chatId,
                                           const QString &text,
                                           float latitude,
                                           float longitude,
                                           unsigned long long replyToMessageId
                                           ):
    TelegramSingleRquest("sendLocation") {

    addArg("chat_id", chatId);
    if (text.size())
        addArg("caption", text);

    addArg("latitude", latitude);
    addArg("longitude", longitude);

    if (replyToMessageId) {
        addArg("reply_to_message_id", replyToMessageId);
    }
}

}
