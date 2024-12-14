//#
//# Copyright (C) 2021-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IBOT_H
#define IBOT_H

#include "qTbot/global.h"
#include "qTbot/iupdate.h"
#include "qTbot/irequest.h"

#include <QMap>
#include <QHash>
#include <QSet>
#include <QFileInfo>
#include <QTimer>

#include <QNetworkReply>
#include <QObject>
#include <QSharedPointer>
#include <qfuture.h>

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
     * @brief The FileType enum is is file types, deffine how we should download a file - as a local object in file system or into virtual memory.
     */
    enum FileType {
        /// The Ram is a Virtual type of download files will save all file data into QFuture bytes array.
        Ram,

        /// The Local file will saved in internal file storage.
        ///  This file type can use the filse system as cache.
        ///  and will doenload file with same id only one time.
        Local
    };

    /**
     * @brief The RequestData class is simple wrapper of request object with path of responce.
     *  If Path of responce is empty then responce will saved in RAM.
     */
    struct RequestData {
        /**
         * @brief request saved request object.
         */
        QSharedPointer<iRequest> request;

        /**
         * @brief responceFilePath path to responce.
         */
        QString responceFilePath = "";

        /**
         * @brief responce This is promise to responce of this requests that will sets back.
         */
        QSharedPointer<QPromise<QByteArray>> responce;
    };

    /**
     * @brief login This method get bae information of the bot from remote server.
     * @param token This is token value for login
     * @return true if login request sent successful else false.
     */
    virtual bool login(const QByteArray& token) = 0;

    /**
     * @brief login This method remove login token of bot.
     */
    virtual void logout();

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
     * @brief deleteMessage This is main method to delete messages.
     * @param chatId This is cahat id wher will be removed message.
     * @param messageId This is removed message id.
     * @return true if request was be prepared successful
     */
    virtual bool deleteMessage(const QVariant& chatId, const QVariant& messageId) = 0;

    /**
     * @brief Get a file by its ID.
     *
     * This function allows you to retrieve a file by its ID.
     *
     * @param fileId The ID of the file to retrieve.
     * @param fileType This is a saving way, by Default will be used a FileType::Ram
     * @return Returns true if the file retrieval operation was successfully initiated and false in case of an error.
     */
    virtual QFuture<QByteArray> getFile(const QString& fileId, FileType fileType = Ram) = 0;

    /**
     * @brief send @a file .
     *
     * @param file This is a file that you want to send.
     * @param chatId id of the chat.
     * @return Returns true if the file sents successful.
     */
    virtual bool sendFile( const QFileInfo& file, const QVariant& chatId) = 0;

    /**
     * @brief sendFile This method setns a file that saved as a bytearray.
     * @param file This is file source.
     * @param fileName This is name of file.
     * @param chatId This is chat of the receivers.
     * @return true if the file will sent successful.
     */
    virtual bool sendFile( const QByteArray& file, const QString& fileName, const QVariant& chatId) = 0;

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
     * @brief takeNextUnreadUpdate This method take a unread update and mark them as read.
     * @return unread message object. If all messages is readed the return nullptr.
     */
    QSharedPointer<iUpdate> takeNextUnreadUpdate();

    /**
     * @brief processed This method return list of processed mesages.
     * @return list of processed messages.
     */
    QSet<unsigned long long> processed() const;

    /**
     * @brief setProcessed This method sets new list of processed mesages.
     * @param newProcessed list of processed messagees.
     */
    virtual void setProcessed(const QSet<unsigned long long> &newProcessed);

    /**
     * @brief reqestLimitPerSecond this is request performence limitation. by default is 20 requests per second
     * @return
     */
    int reqestLimitPerSecond() const;

    /**
     * @brief setReqestLimitPerSecond this method sets new limitation of bot performance.
     * @param newReqestLimitPerSecond this is a new value of performance.
     */
    void setReqestLimitPerSecond(int newReqestLimitPerSecond);

    int parallelActiveNetworkThreads() const;
    void setParallelActiveNetworkThreads(int newParallelActiveNetworkThreads);

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
     * @brief makeMesasge This is factory method tha can create a messages types.
     * @param data This is a raw json data of the ansver.
     * @param args This is list of arguments of the message.
     * @return message object.
     */
    template<class MessageType, class ... Args>
    static QSharedPointer<MessageType> makeMesasge(const QJsonObject& data, Args&& ...args) {
        auto&& ptr = QSharedPointer<MessageType>(new MessageType(std::forward<Args>(args)...));
        ptr->setRawJson(data);

        return ptr;
    }

    /**
     * @brief makeUrl This method prepare a prefix url for http requests.
     * @param request - This is request object for that will be prepared url.
     * @return http request prefix
     */
    virtual QString makeUrl(const QSharedPointer<iRequest>& request) const = 0;

    /**
     * @brief sendRequest This method sent custom requests to the server.
     * @param rquest This is message that will be sent to server.
     * @return future pointer to the request replay.
     */
    QFuture<QByteArray>
    sendRequest(const QSharedPointer<iRequest>& rquest);

    /**
     * @brief sendRequest This method sent custom requests to the server.
     * @param rquest This is message that will be sent to server.
     * @return future pointer to the request replay.
     * @note This is same as a default implementaion execpt save data location,
     *  this method will create new file that located @a pathToResult and save all received data to this location.
     */
    QFuture<QByteArray>
    sendRequest(const QSharedPointer<iRequest>& rquest, const QString& pathToResult);

    /**
     * @brief setToken This is setter of the IBot::token value.
     * @param newToken This is new value of the token.
     */
    void setToken(const QByteArray &newToken);

    /**
     * @brief incomeNewUpdate This method save incomed messages into store.
     */
    void incomeNewUpdate(const QSharedPointer<iUpdate>& message);

    /**
     * @brief markMessageAsProcessed This method remove message from the not processed messages store.
     * @param message This is message that need to be processed.
     */
    void markUpdateAsProcessed(const QSharedPointer<iUpdate>& message);

    /**
     * @brief markMessageAsUnprocessed This method add the message into a not processed messages store.
     * @param message This is message that need to be unprocessed.
     * @note this may be useful for the process edited old messages. Just call this method bofore IBot::incomeNewMessage.
     */
    void markUpdateAsUnprocessed(const QSharedPointer<iUpdate>& message);

    /**
     * @brief markMessageAsUnprocessed This method add the message into a not processed messages store.
     * @param message This is message that need to be unprocessed.
     * @note this may be useful for the process edited old messages. Just call this method bofore IBot::incomeNewMessage.
     */
    void markUpdateAsUnprocessed(unsigned long long messageID);

    /**
     * @brief defaultFileStorageLocation This method return default file storage location.
     * @return default file storage.
     */
    virtual QString defaultFileStorageLocation() const;

    /**
     * @brief handleIncomeNewUpdate This method just emit the sigReceiveUpdate signal.
     * @note you may override this method for filter the sigReceiveUpdate signal or for handling new updates.
     */
    virtual void handleIncomeNewUpdate(const QSharedPointer<iUpdate>& );
signals:
    /**
     * @brief sigReceiveUpdate emit when but receive any updates from users.
     */
    void sigReceiveUpdate(const QSharedPointer<iUpdate>& );

    /**
     * @brief sigStopRequire just custm event for stop bot if tou use services.
     */
    void sigStopRequire();

private slots:
    void handleEcxecuteRequest();
private:
    void setCurrentParallelActiveNetworkThreads(int newParallelActiveNetworkThreads);

    void sendRequestPrivate(const QSharedPointer<iRequest>& rquest,
                            const QSharedPointer<QPromise<QByteArray>> & promiseResult);

    void sendRequestPrivate(const QSharedPointer<iRequest>& rquest,
                            const QString& pathToResult,
                            const QSharedPointer<QPromise<QByteArray> > &promiseResult);

    QNetworkReply *sendRquestImpl(const QSharedPointer<iRequest> &rquest);

    QByteArray _token;
    QString _name;
    QMap<unsigned long long, QSharedPointer<iUpdate>> _notProcessedUpdates;
    QSet<unsigned long long> _processed;
    QNetworkAccessManager *_manager = nullptr;
    QTimer* _requestExecutor = nullptr;
    QList<RequestData> _requestQueue;
    int _currentParallelActiveNetworkThreads = 0;
    int _parallelActiveNetworkThreads = 10;



};

}
#endif // IBOT_H
