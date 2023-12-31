//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef TELEGRAMAUDIO_H
#define TELEGRAMAUDIO_H

#include "telegramfile.h"

namespace qTbot {

/**
 * @brief The TelegramAudio class This is implementation of the audio objects of telegram
 */
class QTBOT_EXPORT TelegramAudio: public TelegramFile
{
public:
    TelegramAudio();
    /**
     * @brief Constructs an Audio object from a JSON object.
     * @param jsonObject The JSON object containing audio data.
     */
    TelegramAudio(const QJsonObject &jsonObject);

    /**
     * @brief Returns the duration of the audio in seconds.
     * @return The duration of the audio.
     */
    int duration() const;

    /**
     * @brief Returns the file name of the audio.
     * @return The file name of the audio.
     */
    QString fileName() const;

    /**
     * @brief Returns the MIME type of the audio.
     * @return The MIME type of the audio.
     */
    QString mimeType() const;

};
}
#endif // TELEGRAMAUDIO_H
