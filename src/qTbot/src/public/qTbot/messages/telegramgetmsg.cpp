//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramgetmsg.h"

namespace qTbot {

TelegramGetMsg::TelegramGetMsg() {

}

QByteArray TelegramGetMsg::makeUpload() const {
    return "/get";
}

bool TelegramGetMsg::isValid() const {
    return true;
}

void TelegramGetMsg::setRawData(const QByteArray &) {
    return;
}

void TelegramGetMsg::setRawJson(const QJsonObject &) {
    return;
}
}
