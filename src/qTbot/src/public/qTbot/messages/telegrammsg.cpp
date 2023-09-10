//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegrammsg.h"
namespace qTbot {


TelegramMsg::TelegramMsg()
{

}

int TelegramMsg::messageId() const {
    return rawJson()["message_id"].toInt();
}

int TelegramMsg::fromId() const {
    return rawJson()["from"]["id"].toInt();
}

bool TelegramMsg::isBot() const {
    return rawJson()["from"]["is_bot"].toBool();
}

QString TelegramMsg::firstName() const {
    return rawJson()["from"]["first_name"].toString();
}

QString TelegramMsg::lastName() const {
    return rawJson()["from"]["last_name"].toString();
}

QString TelegramMsg::username() const {
    return rawJson()["from"]["username"].toString();
}

QString TelegramMsg::languageCode() const {
    return rawJson()["from"]["language_code"].toString();
}

int TelegramMsg::chatId() const {
    return rawJson()["chat"]["id"].toInt();
}

QString TelegramMsg::chatFirstName() const {
    return rawJson()["chat"]["first_name"].toString();
}

QString TelegramMsg::chatLastName() const {
    return rawJson()["chat"]["last_name"].toString();
}

QString TelegramMsg::chatUsername() const {
    return rawJson()["chat"]["username"].toString();
}

QString TelegramMsg::chatType() const {
    return rawJson()["chat"]["type"].toString();
}

qint64 TelegramMsg::date() const {
    return rawJson()["date"].toVariant().toLongLong();
}

QString TelegramMsg::text() const {
    return rawJson()["text"].toString();
}

bool TelegramMsg::contains(const Type &type) {
    return rawJson().contains(type);
}

}
