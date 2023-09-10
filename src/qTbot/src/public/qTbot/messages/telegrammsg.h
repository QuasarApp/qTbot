//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMMSG_H
#define TELEGRAMMSG_H

#include <qTbot/itelegrammessage.h>

namespace qTbot {

/**
 * @brief The TelegramMsg class This class provide general mesasges of telegram.
 * The message object can contains text, geo or link to video,image. all this dates can be contains in one object.
 */
class QTBOT_EXPORT TelegramMsg: public ITelegramMessage
{
public:
    TelegramMsg();

    // ITelegramMessage interface
    void setRawJson(const QJsonObject &newRawJson) override;

    /**
     * @brief date returns date of the snet message.
     * @return message date.
     */
    qint64 date() const;

    /**
     * @brief text returns text that contains this message object.
     * @return text of message.
     */
    QString text() const;
};

}
#endif // TELEGRAMMSG_H
