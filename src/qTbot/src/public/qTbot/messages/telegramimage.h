//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMIMAGE_H
#define TELEGRAMIMAGE_H

#include "telegramfile.h"

namespace qTbot {

/**
 * @brief The TelegramImage class This is implementation of the photos of telegram
 */
class TelegramImage: public TelegramFile
{
public:
    TelegramImage();

    /**
     * @brief Constructs a Photo object from a JSON object.
     * @param jsonObject The JSON object containing photo data.
     */
    TelegramImage(const QJsonObject &jsonObject);

    /**
     * @brief Returns the width of the photo.
     * @return The width of the photo.
     */
    int width() const;

    /**
     * @brief Returns the height of the photo.
     * @return The height of the photo.
     */
    int height() const;
};
}
#endif // TELEGRAMIMAGE_H
