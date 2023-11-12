//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMSENDPHOTO_H
#define TELEGRAMSENDPHOTO_H

#include "telegramsendfile.h"

namespace qTbot {

/**
 * @brief The TelegramSendPhoto class using to sending photos on chat
 */
class TelegramSendPhoto: public TelegramSendFile
{
public:
    TelegramSendPhoto(const QVariant &chatId,
                      const QString &text,
                      const QString &fileName,
                      const QByteArray& data,
                      unsigned long long replyToMessageId = 0,
                      const QMap<QString, QSharedPointer<QJsonObject>>& extraObjects = {}
                      );

    TelegramSendPhoto(const QVariant &chatId,
                      const QString &text,
                      const QFileInfo &file,
                      unsigned long long replyToMessageId = 0,
                      const QMap<QString, QSharedPointer<QJsonObject>>& extraObjects = {}
                      );

};
}
#endif // TELEGRAMSENDPHOTO_H
