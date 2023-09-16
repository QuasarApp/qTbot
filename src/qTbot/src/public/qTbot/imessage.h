//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef IMESSAGE_H
#define IMESSAGE_H

#include "qTbot/global.h"
#include <QByteArray>


namespace qTbot {

/**
 * @brief The iMessage class - is main interface for all messages objects.
 * @note Theall message objects posible to create only inner bot object using the IBot::makeMesasge method.
 * @see IBot::sigReceiveMessage
 * @see IBot::incomeNewMessage
 * @see IBot::markMessageAsProcessed
 * @see IBot::takeNextUnreadMessage
 * @see IBot::makeMesasge
 */
class QTBOT_EXPORT iMessage
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

    /**
     * @brief from This virtual function should return name of the user that sent this message to bot.
     * @return id of the sender.
     */
    virtual QString from() const = 0;

    /**
     * @brief messageId This method returns numeric id of the message.
     * @return numeric id of the message.
     */
    virtual unsigned long long messageId() const = 0;

private:

    QByteArray _rawData;
};
}
#endif // IMESSAGE_H
