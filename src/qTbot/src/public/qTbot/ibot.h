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

#include "ifile.h"

#include <QMap>
#include <QHash>
#include <QSet>

#include <QNetworkReply>
#include <QObject>
#include <QSharedPointer>

namespace qTbot {

class ReplayData;

/**
 * @brief The IBot class Base interface for all chat-bots objcts.
 */
class QTBOT_EXPORT IBot: public QObject
{
    Q_OBJECT
public:
    IBot();
    ~IBot();

    /**
     * @brief login This method get bae information of the bot from remote server.
     * @param token This is token value for login
     * @return true if login request sent successful else false.
     */
    virtual bool login(const QByteArray& token) = 0;

    /**
     * @brief sendMessage This method sents text to the selected chat.
     * @param chatId This is selected chat id
     * @param text This is text that neet to sent.
     * @return true if data sents successful else false.
     *
     * @note the specific implementations of this interface can have a different method for sending.
    */
    virtual bool sendMessage(const QVariant& chatId, const QString& text) = 0;


    /**
     * @brief Get a file by its ID.
     *
     * This function allows you to retrieve a file by its ID.
     *
     * @param fileId The ID of the file to retrieve.
     * @param fileType This is a saving way, by Default will be used a iFile::Type::Ram
     * @return Returns true if the file retrieval operation was successfully initiated and false in case of an error.
     */
    virtual QSharedPointer<iFile> getFile(const QString& fileId, iFile::Type fileType = iFile::Type::Ram) = 0;

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

    /**
     * @brief processed This method return list of processed mesages.
     * @return list of processed messages.
     */
    QSet<unsigned long long> processed() const;

    /**
     * @brief setProcessed This method sets new list of processed mesages.
     * @param newProcessed list of processed messagees.
     */
    void setProcessed(const QSet<unsigned long long> &newProcessed);

protected:

    /**
     * @brief makeMesasge This is factory method tha can create a messages types.
     * @param data This is a raw data of the ansver.
     * @param args This is list of arguments of the message.
     * @return message object.
     */
    template<class MessageType, class ... Args>
    static QSharedPointer<MessageType> makeMesasge(const QByteArray& data, Args&& ...args) {
        auto&& ptr = QSharedPointer<MessageType>(new MessageType(std::forward<Args>(args)...));
        ptr->setRawData(data);

        return ptr;
    }

    /**
     * @brief makeUrl This method prepare a prefix url for http requests.
     * @param request - This is request object for that will be prepared url.
     * @return http request prefix
     */
    virtual QByteArray makeUrl(const QSharedPointer<iRequest>& request) const = 0;

    /**
     * @brief sendRequest This method sent custom requests to the server.
     * @param rquest This is message that will be sent to server.
     * @return shared pointer to the request replay.
     * @note The raplay will be removed from local storage only after error or finishing, If you want to save replay just make local copy of the shared pointer.
     */
    QSharedPointer<QNetworkReply> sendRequest(const QSharedPointer<iRequest>& rquest);

    /**
     * @brief setToken This is setter of the IBot::token value.
     * @param newToken This is new value of the token.
     */
    void setToken(const QByteArray &newToken);

    /**
     * @brief incomeNewMessage This method save income message into store.
     */
    virtual void incomeNewMessage(const QSharedPointer<iMessage>& message);

    /**
     * @brief markMessageAsProcessed This method remove message from the not processed messages store.
     * @param message This is message that need to be processed.
     */
    void markMessageAsProcessed(const QSharedPointer<iMessage>& message);

    /**
     * @brief markMessageAsUnprocessed This method add the message into a not processed messages store.
     * @param message This is message that need to be unprocessed.
     * @note this may be useful for the process edited old messages. Just call this method bofore IBot::incomeNewMessage.
     */
    void markMessageAsUnprocessed(const QSharedPointer<iMessage>& message);

    /**
     * @brief markMessageAsUnprocessed This method add the message into a not processed messages store.
     * @param message This is message that need to be unprocessed.
     * @note this may be useful for the process edited old messages. Just call this method bofore IBot::incomeNewMessage.
     */
    void markMessageAsUnprocessed(unsigned long long messageID);

    /**
     * @brief defaultFileStorageLocation This method return default file storage location.
     * @return default file storage.
     */
    virtual QString defaultFileStorageLocation() const;
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
    QNetworkAccessManager *_manager = nullptr;

    QMap<size_t,QSharedPointer<QNetworkReply>> _replayStorage;
};

}
#endif // IBOT_H
