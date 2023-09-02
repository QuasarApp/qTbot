//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramtextmsg.h"
namespace qTbot {

TelegramTextMsg::TelegramTextMsg() {

}

void TelegramTextMsg::setRawJson(const QJsonObject &newRawJson) {
    setText(newRawJson.value("text").toString());
    ITelegramMessage::setRawJson(newRawJson);
}

QString TelegramTextMsg::text() const {
    return _text;
}

void TelegramTextMsg::setText(const QString &newText) {
    _text = newText;
}
}
