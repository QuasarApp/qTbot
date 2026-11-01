//#
//# Copyright (C) 2023-2026 QuasarApp.
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
 * @brief The TelegramSendFile class is the base class for uploading files to the server.
 */
class TelegramSendFile: public TelegramSingleRquest
{
public:

    /**
     * @brief TelegramSendFile prepares the send file request from a byte array.
     * @param request This is the request name (command) of the telegram api.
     * @param fileName This is the displayed name of the file.
     * @param fileType This is the type of the file (for example photo or document).
     * @param data This is the file source data.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramSendFile(const QString &request,
                     const QString &fileName,
                     const QString &fileType,
                     const QByteArray& data,
                     const TelegramArgs &args,
                     const QHash<QString, QSharedPointer<QJsonObject> > &extraObjects = {});

    /**
     * @brief TelegramSendFile prepares the send file request from a file.
     * @param request This is the request name (command) of the telegram api.
     * @param file This is the file that will be uploaded.
     * @param args This is the general arguments of the request (include the target chat id).
     * @param extraObjects This is the additional objects of the telegram message (json).
     */
    TelegramSendFile(const QString &request,
                     const QFileInfo &file,
                     const TelegramArgs &args,
                     const QHash<QString, QSharedPointer<QJsonObject> > &extraObjects = {});

    /**
     * @brief method Returns the method of the request. The file upload requests always use the Upload method.
     * @return the Upload request method.
     */
    RequestMethod method() const override;

protected:
    /**
     * @brief type Returns the file type. By default it is REQUEST_UPLOAD_FILE_KEY.
     * @return the file type key.
     */
    virtual QString type() const;
};
}
#endif // TELEGRAMSENDFILE_H
