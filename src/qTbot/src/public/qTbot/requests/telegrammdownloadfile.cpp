//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegrammdownloadfile.h"

namespace qTbot {

TelegrammDownloadFile::TelegrammDownloadFile(const QByteArray &filePath):
    TelegramSingleRquest(filePath, {}) {

}

QByteArray TelegrammDownloadFile::baseAddress() const {
    return "https://api.telegram.org/file";
}
}
