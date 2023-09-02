//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramrestbot.h"

namespace qTbot {

TelegramRestBot::TelegramRestBot()
{

}

bool TelegramRestBot::login(const QByteArray &token) {
    ITelegramBot::login(token);
}

bool TelegramRestBot::sendMessage(const QSharedPointer<iMessage> &message) {

}
}
