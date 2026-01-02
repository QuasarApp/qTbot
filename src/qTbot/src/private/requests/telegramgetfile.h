//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMGETFILE_H
#define TELEGRAMGETFILE_H

#include "telegramsinglerquest.h"

namespace qTbot {

/**
 * @brief The TelegramGetFile class build http request for the getting files from tellgram messager.
 */
class TelegramGetFile final: public TelegramSingleRquest
{
public:
    TelegramGetFile(const QString& fileId);
};

}
#endif // TELEGRAMGETFILE_H
