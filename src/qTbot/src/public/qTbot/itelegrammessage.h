//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef ITELEGRAMMESSAGE_H
#define ITELEGRAMMESSAGE_H

#include "imessage.h"
#include "qjsonobject.h"

namespace qTbot {

/**
 * @brief The ItelegramMessage class This is base interface of the all telegram messages.
 */
class QTBOT_EXPORT ITelegramMessage: public iMessage
{
public:
    ITelegramMessage();

    // iMessage interface
public:
    bool isValid() const override;
    QByteArray makeUpload() const override;

    /**
     * @brief rawJson Telegram use rest api with json objects. So all received messages will be parsed in to jsobject.
     * @return js implementation of object.
     */
    const QJsonObject& rawJson() const;

    /**
     * @brief setRawJson this method convert jsobject into telegram message.
     * @param newRawJson new data for telegram message.
     */
    virtual void setRawJson(const QJsonObject &newRawJson);

    void setRawData(const QByteArray &newRawData) override;


private:
    QJsonObject _rawJson;

};

}
#endif // ITELEGRAMMESSAGE_H
