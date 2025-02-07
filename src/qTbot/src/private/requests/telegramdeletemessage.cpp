//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramdeletemessage.h"
namespace qTbot {

TelegramDeleteMessage::TelegramDeleteMessage(const QVariant &chatId,
                                             const QVariant &messageId):
    TelegramSingleRquest("deleteMessage")

{

    addArg("chat_id", chatId);
    addArg("message_id", messageId);
}
}
