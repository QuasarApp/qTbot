//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramupdateanswer.h"

namespace qTbot {

TelegramUpdateAnswer::TelegramUpdateAnswer()
{

}

QJsonValue TelegramUpdateAnswer::result() const {
    return rawJson().value("result");
}

int TelegramUpdateAnswer::errorCode() const {
    return rawJson().value("error_code").toInt();
}

QString TelegramUpdateAnswer::errorDescription() const {
    return rawJson().value("description").toString();
}

QString TelegramUpdateAnswer::from() const {
    return "";
}

QVariant TelegramUpdateAnswer::chatId() const {
    return {};
}

unsigned long long TelegramUpdateAnswer::updateId() const {
    return 0;
}

bool TelegramUpdateAnswer::isValid() const {
    return rawJson().value("ok").toBool();
}

}
