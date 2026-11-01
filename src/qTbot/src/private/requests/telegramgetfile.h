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
 * @brief The TelegramGetFile class builds an http request for getting files from the telegram messenger.
 */
class TelegramGetFile final: public TelegramSingleRquest
{
public:
    /**
     * @brief TelegramGetFile prepares the get file request.
     * @param fileId This is the id of the file that needs to be downloaded.
     */
    TelegramGetFile(const QString& fileId);
};

}
#endif // TELEGRAMGETFILE_H
