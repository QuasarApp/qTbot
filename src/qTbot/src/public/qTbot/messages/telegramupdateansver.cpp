//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramupdateansver.h"

namespace qTbot {

TelegramUpdateAnsver::TelegramUpdateAnsver()
{

}

QJsonValue TelegramUpdateAnsver::result() const {
    return rawJson().value("result");
}

QString TelegramUpdateAnsver::from() const {
    return "";
}

QVariant TelegramUpdateAnsver::chatId() const {
    return {};
}

unsigned long long TelegramUpdateAnsver::messageId() const {
    return 0;
}

bool TelegramUpdateAnsver::isValid() const {
    return rawJson().value("ok").toBool();
}

}
