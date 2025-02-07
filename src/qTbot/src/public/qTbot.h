//#
//# Copyright (C) 2021-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qTbot/global.h"
#include <QString>

inline void initqTbotResources() { Q_INIT_RESOURCE(qTbot); }

namespace qTbot {

/**
 * @brief init main initialize method of The qTbot library
 * @return true if library initialized successfull
 */
bool QTBOT_EXPORT init();

/**
 * @brief version This method return string value of a library version
 * @return string value of a library version
 */
QString QTBOT_EXPORT version();

};
