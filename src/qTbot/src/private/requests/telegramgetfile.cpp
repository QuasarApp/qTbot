//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramgetfile.h"

namespace qTbot {

TelegramGetFile::TelegramGetFile(const QString &fileId):
    TelegramSingleRquest("getFile", {{"file_id", fileId}}) {

}


}
