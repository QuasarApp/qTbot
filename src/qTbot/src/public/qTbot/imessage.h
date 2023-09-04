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
     * @brief userId This is id of user that sent this message or must be receive this.
     * @return user id.
     */
    const QByteArray& userId() const;

    /**
     * @brief setUserId This method sets new value of the message user.
     * @param newUserId This new value of user.
     */
    void setUserId(const QByteArray &newUserId);

    /**
     * @brief makeUpload This method prepare data to upload;
     * @return data array prepared to sending.
     */
    virtual QByteArray makeUpload() const = 0;

    /**
     * @brief isValid return true if the message is valid else false.
     * @return true if the message is valid else false.
     */
    virtual bool isValid() const;



private:
    QByteArray _rawData;
    QByteArray _userId;
};
}
#endif // IMESSAGE_H
