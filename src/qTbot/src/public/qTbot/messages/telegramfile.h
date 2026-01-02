//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMFILE_H
#define TELEGRAMFILE_H

#include "qTbot/ijsonbasedobject.h"
namespace qTbot {

/**
 * @brief The TelegramFile class is base class for all files.
 */
class QTBOT_EXPORT TelegramFile: public IJsonBasedObject
{
public:
    TelegramFile();

    /**
     * @brief Constructs a Photo object from a JSON object.
     * @param jsonObject The JSON object containing photo data.
     */
    TelegramFile(const QJsonObject &jsonObject);

    /**
     * @brief Returns the file ID of the photo.
     * @return The file ID of the photo.
     */
    QString fileId() const;

    /**
     * @brief Returns the unique ID of the photo.
     * @return The unique ID of the photo.
     */
    QString fileUniqueId() const;

    /**
     * @brief Returns the file size of the photo.
     * @return The file size of the photo.
     */
    int fileSize() const;

    /**
     * @brief Returns the file path to get from web.
     * @return The file size of the photo. return empty string if file alredy used.
     * @note posible to get file from web only one time after invoke the getFile method. If you invoke this method 2 times on the second time you receive empty string. This is rooles of the telegram backend. see https://telegram-bot-sdk.readme.io/reference/getfile
     */
    [[nodiscard("This method return path only one time, plese no discard this.")]]
    QString takePath();

private:
    bool _used = false;
};
}
#endif // TELEGRAMFILE_H
