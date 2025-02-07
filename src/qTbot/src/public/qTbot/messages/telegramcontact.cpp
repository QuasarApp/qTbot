//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramcontact.h"

namespace qTbot {

TelegramContact::TelegramContact()
{
    
}

TelegramContact::TelegramContact(const QJsonObject &jsonObject): IJsonBasedObject(jsonObject) {

}


unsigned long long TelegramContact::userIdInt() const {
    return rawJson()["user_id"].toInteger();
}

QVariant TelegramContact::userId() const {
    return rawJson()["user_id"];
}

QString TelegramContact::firstName() const {
    return rawJson()["first_name"].toString();
}

QString TelegramContact::lastName() const {
    return rawJson()["last_name"].toString();
}

QString TelegramContact::username() const {
    return rawJson()["username"].toString();
}

QString TelegramContact::phone() const {
    return rawJson()["phone_number"].toString();
}

QString TelegramContact::languageCode() const {
    return rawJson()["language_code"].toString();
}
}
