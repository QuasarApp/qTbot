//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMMDOWNLOADFILE_H
#define TELEGRAMMDOWNLOADFILE_H

#include "telegramsinglerquest.h"

namespace qTbot {

/**
 * @brief The TelegrammDownloadFile class prepare link to download telegramm files.
 */
class TelegrammDownloadFile final: public TelegramSingleRquest
{
public:
    TelegrammDownloadFile(const QString &filePath);

    QString baseAddress() const override;

};

}
#endif // TELEGRAMMDOWNLOADFILE_H
