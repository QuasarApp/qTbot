//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "telegramsinglerquest.h"


namespace qTbot {

TelegramSingleRquest::TelegramSingleRquest(const QByteArray &request) {
    _request = request;
}

QByteArray TelegramSingleRquest::makeUpload() const {
    return "/" + _request;
}

}
