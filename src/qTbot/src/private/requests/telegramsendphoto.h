//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMSENDPHOTO_H
#define TELEGRAMSENDPHOTO_H

#include "telegramsendfile.h"

namespace qTbot {

/**
 * @brief The TelegramSendPhoto class is used for sending photos into the chat.
 */
class TelegramSendPhoto: public TelegramSendFile
{
public:
    /**
     * @brief TelegramSendPhoto prepares the send photo request from a byte array.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param fileName This is the displayed name of the photo.
     * @param data This is the photo source data.
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramSendPhoto(const TelegramArgs &args,
                      const QString &fileName,
                      const QByteArray& data,
                      const ExtraJsonObjects& extraObjects = {}
                      );

    /**
     * @brief TelegramSendPhoto prepares the send photo request from a file.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param file This is the file that contains the photo.
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramSendPhoto(const TelegramArgs &args,
                      const QFileInfo &file,
                      const ExtraJsonObjects& extraObjects = {}
                      );

};
}
#endif // TELEGRAMSENDPHOTO_H
