//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSENDDOCUMENT_H
#define TELEGRAMSENDDOCUMENT_H

#include "telegramsendfile.h"


namespace qTbot {

/**
 * @brief The TelegramSendDocument class sends a document into the chat.
 */
class TelegramSendDocument: public TelegramSendFile
{
public:
    /**
     * @brief TelegramSendDocument prepares the send document request from a byte array.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param fileName This is the displayed name of the document.
     * @param data This is the document source data.
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramSendDocument(const TelegramArgs &args,
                         const QString &fileName,
                         const QByteArray& data,
                         const ExtraJsonObjects& extraObjects = {});

    /**
     * @brief TelegramSendDocument prepares the send document request from a file.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param file This is the file that contains the document.
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramSendDocument(const TelegramArgs &args,
                         const QFileInfo &file,
                         const ExtraJsonObjects& extraObjects = {});

};
}
#endif // TELEGRAMSENDDOCUMENT_H
