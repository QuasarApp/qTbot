//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegrameditmessagereplymarkup.h"

namespace qTbot {

TelegramEditMessageReplyMarkup::TelegramEditMessageReplyMarkup(const QVariant& idEditedMessage,
                                                               const TelegramArgs& args,
                                                               const ExtraJsonObjects &extraObjects):
    TelegramEditMessage(idEditedMessage, args, extraObjects)
{
    setRequest("editMessageReplyMarkup");
}
}
