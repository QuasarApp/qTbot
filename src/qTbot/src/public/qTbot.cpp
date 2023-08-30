//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qTbot.h"


namespace qTbot {

bool init() {
    initqTbotResources();
    return true;
}

QString version() {
    return QTBOT_VERSION;
}


}
