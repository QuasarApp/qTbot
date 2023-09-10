//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef IMESSAGE_H
#define IMESSAGE_H

#include "irequest.h"
#include <QByteArray>


namespace qTbot {

/**
 * @brief The iMessage class - is main interface for all messages objects.
 * @see IBot::sendMessage
 * @see IBot::sigReceiveMessage
 */
class QTBOT_EXPORT iMessage: public iRequest
{
public:
    iMessage();

    /**
     * @brief rawData returns raw data of the message.
     *  The raw data is not parsed value form the server.
     * @return raw data from the server.
     */
    const QByteArray &rawData() const;

    /**
     * @brief setRawData This method sets new raw data value.
     * @param newRawData This is new value of the rawData.
     */
    virtual void setRawData(const QByteArray &newRawData);

    /**
     * @brief isValid return true if the message is valid else false.
     * @return true if the message is valid else false.
     */
    virtual bool isValid() const;

private:
    QByteArray _rawData;
};
}
#endif // IMESSAGE_H
