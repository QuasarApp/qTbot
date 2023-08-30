//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IBOT_H
#define IBOT_H

#include "qTbot/global.h"
#include "qTbot/imessage.h"

#include <QSharedPointer>

namespace qTbot {

/**
 * @brief The IBot class Base interface for all chat-bots objcts.
 */
class QTBOT_EXPORT IBot
{
public:
    IBot();

    /**
     * @brief sendMessage This method should be send message to the server.
     * @param message This is data for sending.
     * @return true if the message sent successful else false.
     */
    virtual bool sendMessage(const QSharedPointer<iMessage>& message) = 0;

    /**
     * @brief token This is token value for authication on the remote server (bot)
     * @return auth toke of the bot.
     */
    QByteArray &token() const;

    /**
     * @brief setToken This is setter of the IBot::token value.
     * @param newToken This is new value of the token.
     */
    void setToken(const QByteArray &newToken);

    /**
     * @brief name This is name of the bot. usualy it fields will be received from the server after autication.
     * @return
     */
    QString name() const;

    /**
     * @brief setName This method sets new value for the IBot::name field.
     * @param newName
     */
    void setName(const QString &newName);

private:
    QByteArray& _token;
    QString _name;

signals:
    /**
     * @brief receiveMessage emit when but receive any updates from users.
     */
    void receiveMessage(QSharedPointer<iMessage> );

};
}
#endif // IBOT_H
