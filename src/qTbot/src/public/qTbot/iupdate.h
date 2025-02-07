//#
//# Copyright (C) 2021-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef IUPDATE_H
#define IUPDATE_H

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
class QTBOT_EXPORT iUpdate
{
public:
    iUpdate();

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
     * @brief from This virtual function should return name of the chat when sent this message to bot.
     * @return id of the sender.
     */
    virtual QVariant chatId() const = 0;

    /**
     * @brief updateId This method returns numeric id of the update.
     * @return numeric id of the update.
     */
    virtual unsigned long long updateId() const = 0;

private:

    QByteArray _rawData;
};
}
#endif // IUPDATE_H
