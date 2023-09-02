//#
//# Copyright (C) 2018-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "itelegrambot.h"

#include <qTbot/messages/telegramgetmsg.h>

namespace qTbot {

ITelegramBot::ITelegramBot() {

}

bool ITelegramBot::login(const QByteArray &token) {
    setToken(token);

    TelegramGetMsg msg;
    auto getInfoRquest = makePrefix() + msg.makeUpload();


}

QByteArray ITelegramBot::makePrefix() const {
    return "";
}

}
