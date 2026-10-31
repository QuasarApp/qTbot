//#
//# Copyright (C) 2021-2026 QuasarApp.
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
 * @brief The iUpdate class is the main interface for all update objects.
 * @note All update objects are possible to create only inside the bot object using the IBot::makeMesasge method.
 * @see IBot::sigReceiveUpdate
 * @see IBot::incomeNewUpdate
 * @see IBot::markUpdateAsProcessed
 * @see IBot::takeNextUnreadUpdate
 * @see IBot::makeMesasge
 */
class QTBOT_EXPORT iUpdate
{
public:
    /**
     * @brief iUpdate default constructor.
     */
    iUpdate();

    /**
     * @brief rawData returns the raw data of the update.
     * The raw data is the not parsed value from the server.
     * @return raw data from the server.
     */
    const QByteArray &rawData() const;

    /**
     * @brief setRawData This method sets a new raw data value.
     * @param newRawData This is the new value of the rawData.
     */
    virtual void setRawData(const QByteArray &newRawData);

    /**
     * @brief isValid returns true if the update is valid else false.
     * @return true if the update is valid else false.
     */
    virtual bool isValid() const;

    /**
     * @brief from This virtual function should return the id of the user that sent this update to the bot.
     * @return id of the sender.
     */
    virtual QString from() const = 0;

    /**
     * @brief chatId This virtual function should return the id of the chat that sent this update to the bot.
     * @return id of the chat.
     */
    virtual QVariant chatId() const = 0;

    /**
     * @brief updateId This method returns the numeric id of the update.
     * @return numeric id of the update.
     */
    virtual unsigned long long updateId() const = 0;

private:

    QByteArray _rawData;
};
}
#endif // IUPDATE_H
