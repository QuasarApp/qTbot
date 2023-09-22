//#
//# Copyright (C) 2023-2023 QuasarApp.
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
class TelegramFile: public IJsonBasedObject
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
};
}
#endif // TELEGRAMFILE_H
