//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#ifndef TELEGRAMSENDFILE_H
#define TELEGRAMSENDFILE_H

#include "qfileinfo.h"
#include "requests/telegramsinglerquest.h"
namespace qTbot {


/**
 * @brief The TelegramSendFile class Base clas for upload files to server
 */
class TelegramSendFile: public TelegramSingleRquest
{
public:

    TelegramSendFile(const QString &request,
                     const QVariant &chatId,
                     const QString &text,
                     const QString &fileName,
                     const QByteArray& data);

    TelegramSendFile(const QString &request,
                     const QVariant &chatId,
                     const QString &text,
                     const QFileInfo &file);

    // iRequest interface
public:
    RequestMethod method() const override;
};
}
#endif // TELEGRAMSENDFILE_H
