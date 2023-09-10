//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramtextmsg.h"
namespace qTbot {

TelegramMsg::TelegramMsg() {

}

qint64 TelegramMsg::date() const {
    return rawJsonObject()["date"].toVariant().toLongLong();
}

QString TelegramMsg::text() const {
    return rawJsonObject()["text"].toString();
}

}
