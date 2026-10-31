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
    /**
     * @brief TelegramFile default constructor.
     */
    TelegramFile();

    /**
     * @brief Constructs a File object from a JSON object.
     * @param jsonObject The JSON object containing file data.
     */
    TelegramFile(const QJsonObject &jsonObject);

    /**
     * @brief Returns the file ID of the file.
     * @return The file ID of the file.
     */
    QString fileId() const;

    /**
     * @brief Returns the unique ID of the file.
     * @return The unique ID of the file.
     */
    QString fileUniqueId() const;

    /**
     * @brief Returns the file size of the file.
     * @return The file size of the file.
     */
    int fileSize() const;

    /**
     * @brief Returns the file path to get from the web.
     * @return The file path to get from the web. Returns an empty string if the file was already used.
     * @note It is possible to get a file from the web only one time after invoking the getFile method. If you invoke this method twice, on the second time you receive an empty string. This is a rule of the telegram backend. See https://core.telegram.org/bots/api#file
     */
    [[nodiscard("This method return path only one time, please don't discard it.")]]
    QString takePath();

private:
    bool _used = false;
};
}
#endif // TELEGRAMFILE_H
