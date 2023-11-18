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

#include <qTbot/telegramargs.h>

#define TELEGRAM_PHOTO "photo"
#define TELEGRAM_DOCUMENT "document"

namespace qTbot {

/**
 * @brief The TelegramSendFile class Base clas for upload files to server
 */
class TelegramSendFile: public TelegramSingleRquest
{
public:

    TelegramSendFile(const QString &request,
                     const QString &fileName,
                     const QString &fileType,
                     const QByteArray& data,
                     const TelegramArgs &args,
                     const QHash<QString, QSharedPointer<QJsonObject> > &extraObjects = {});

    TelegramSendFile(const QString &request,
                     const QFileInfo &file,
                     const TelegramArgs &args,
                     const QHash<QString, QSharedPointer<QJsonObject> > &extraObjects = {});

    RequestMethod method() const override;

protected:
    /**
     * @brief type return type file. By Default it is REQUEST_UPLOAD_FILE_KEY
     * @return
     */
    virtual QString type() const;
};
}
#endif // TELEGRAMSENDFILE_H
