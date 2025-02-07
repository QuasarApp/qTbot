//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSENDDOCUMENT_H
#define TELEGRAMSENDDOCUMENT_H

#include "telegramsendfile.h"


namespace qTbot {

/**
 * @brief The TelegramSendDocument class sents document into chat
 */
class TelegramSendDocument: public TelegramSendFile
{
public:
    TelegramSendDocument(const TelegramArgs &args,
                         const QString &fileName,
                         const QByteArray& data,
                         const ExtraJsonObjects& extraObjects = {});

    TelegramSendDocument(const TelegramArgs &args,
                         const QFileInfo &file,
                         const ExtraJsonObjects& extraObjects = {});

};
}
#endif // TELEGRAMSENDDOCUMENT_H
