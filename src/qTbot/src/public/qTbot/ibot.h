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
#include "qTbot/irequest.h"

#include <QMap>
#include <QHash>
#include <QSet>

#include <QObject>
#include <QSharedPointer>

namespace qTbot {

/**
 * @brief The IBot class Base interface for all chat-bots objcts.
 */
class QTBOT_EXPORT IBot: public QObject
{
    Q_OBJECT
public:
    IBot();

    /**
     * @brief Responce - This is labda for server responces.
     *  The first argument of a call back function is is request that was sent, second is server responce.
     *  And error code - 0 if request finished successfull
     */
    using Responce = std::function<void(const QSharedPointer<iRequest>& request,
                                        const QSharedPointer<iMessage>& responce,
                                        unsigned int err)>;

    /**
     * @brief login This method get bae information of the bot from remote server.
     * @param token This is token value for login
     * @return true if login request sent successful else false.
     */
    virtual bool login(const QByteArray& token) = 0;

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
    const QByteArray &token() const;

    /**
     * @brief name This is name of the bot. usualy it fields will be received from the server after autication.
     * @return name if the bot.
     */
    const QString& name() const;

    /**
     * @brief setName This method sets new value for the IBot::name field.
     * @param newName This is new value of the IBot::name property
     */
    void setName(const QString &newName);

    /**
     * @brief takeNextUnreadMessage This method take a unread message and mark them as read.
     * @return unread message object. If all messages is readed the return nullptr.
     */
    QSharedPointer<iMessage> takeNextUnreadMessage();

protected:

    /**
     * @brief makeMesasge This is factory method tha can create a messages types.
     * @param args This is list of arguments of the message.
     * @return message object.
     */
    template<class MessageType, class ... Args>
    static QSharedPointer<MessageType> makeMesasge(Args&& ...args) {
        return QSharedPointer<MessageType>(new MessageType(std::forward<Args>(args)...));
    }

    /**
     * @brief sendRequest This method sent custom requests to the server.
     * @param rquest This is message that will be sent to server.
     * @param cb This is call back function for the responce.
     * @return true if the request will sent successful else false.
     */
    virtual bool sendRequest(const QSharedPointer<iRequest>& rquest, const Responce& cb) = 0;

    /**
     * @brief setToken This is setter of the IBot::token value.
     * @param newToken This is new value of the token.
     */
    void setToken(const QByteArray &newToken);

    /**
     * @brief incomeNewMessage This method save income message into store.
     */
    void incomeNewMessage(const QSharedPointer<iMessage>& message);

    /**
     * @brief markMessageAsProcessed This method remove message from the not processed messages store.
     * @param message This is message that need to be processed.
     */
    void markMessageAsProcessed(const QSharedPointer<iMessage>& message);

signals:
    /**
     * @brief sigReceiveMessage emit when but receive any updates from users.
     */
    void sigReceiveMessage(const QSharedPointer<iMessage>& );

private:
    QByteArray _token;
    QString _name;
    QMap<unsigned long long, QSharedPointer<iMessage>> _notProcessedMessages;
    QSet<unsigned long long> _processed;


};

}
#endif // IBOT_H
