//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMMDOWNLOADFILE_H
#define TELEGRAMMDOWNLOADFILE_H

#include "telegramsinglerquest.h"

namespace qTbot {

/**
 * @brief The TelegrammDownloadFile class prepares the link to download telegram files.
 */
class TelegrammDownloadFile final: public TelegramSingleRquest
{
public:
    /**
     * @brief TelegrammDownloadFile prepares the download file request.
     * @param filePath This is the file path that will be returned by the telegram server.
     */
    TelegrammDownloadFile(const QString &filePath);

    QString baseAddress() const override;

};

}
#endif // TELEGRAMMDOWNLOADFILE_H
