//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "telegramgetupdate.h"

namespace qTbot {

TelegramGetUpdate::TelegramGetUpdate(unsigned long long offset): TelegramSingleRquest("getUpdates"){
    addArg("offset", offset);
    addArg("timeout", 30);
    setPriority(UngeredPriority);

}
}
