//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegrameditmessage.h"

namespace qTbot {

TelegramEditMessage::TelegramEditMessage(const QVariant &idEditedMessage,
                                         const TelegramArgs &args,
                                         const ExtraJsonObjects &extraObjects):
    TelegramSendMsg(args, extraObjects){

    setRequest("editMessageText");
    addArg("message_id", idEditedMessage);
}

}
