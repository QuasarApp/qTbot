//#
//# Copyright (C) 2021-2026 QuasarApp.
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
 * @brief The IBot class Base interface for all chat-bot objects.
 */
class QTBOT_EXPORT IBot: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief IBot default constructor. Initializes the network access manager and the request executor.
     */
    IBot();

    /**
     * @brief ~IBot destructor. Cancels pending requests and frees all network resources.
     */
    ~IBot();

    /**
     * @brief The FileType enum is a list of file types. It defines how a file should be downloaded - as a local object in the file system or into virtual memory.
     */
    enum FileType {
        /**
         * @brief Ram virtual file type. All file data will be saved into a QFuture bytes array.
         */
        Ram,

        /**
         * @brief Local file type. The file will be saved in the internal file storage.
         * This file type can use the file system as a cache
         * and will download a file with the same id only one time.
         */
        Local
    };

    /**
     * @brief The RequestData class is a simple wrapper of a request object with the path of the response.
     * If the path of the response is empty, then the response will be saved in RAM.
     */
    struct RequestData {
        /**
         * @brief request the saved request object.
         */
        QSharedPointer<iRequest> request;

        /**
         * @brief responceFilePath path to the response file.
         */
        QString responceFilePath = "";

        /**
         * @brief responce this is a promise of the response of this request that will be set back.
         */
        QSharedPointer<QPromise<QByteArray>> responce;
    };

    /**
     * @brief login This method gets basic information of the bot from the remote server.
     * @param token This is the token value for login
     * @return true if the login request was sent successfully else false.
     */
    virtual bool login(const QByteArray& token) = 0;

    /**
     * @brief logout This method removes the login token of the bot.
     */
    virtual void logout();

    /**
     * @brief sendMessage This method sends text to the selected chat.
     * @param chatId This is the selected chat id
     * @param text This is the text that needs to be sent.
     * @param priority This is the priority of the request in the send queue.
     * @return true if the data was sent successfully else false.
     *
     * @note the specific implementations of this interface can have a different method for sending.
    */
    virtual bool sendMessage(const QVariant& chatId, const QString& text, iRequest::RequestPriority priority = iRequest::NormalPriority) = 0;

    /**
     * @brief deleteMessage This is the main method to delete messages.
     * @param chatId This is the chat id where the message will be removed.
     * @param messageId This is the removed message id.
     * @return true if the request was prepared successfully
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
     * @brief sendFile This method sends the selected file to the chat.
     *
     * @param file This is a file that you want to send.
     * @param chatId id of the chat.
     * @return Returns true if the file was sent successfully.
     */
    virtual bool sendFile( const QFileInfo& file, const QVariant& chatId) = 0;

    /**
     * @brief sendFile This method sends a file that is saved as a byte array.
     * @param file This is the file source data.
     * @param fileName This is the name of the file.
     * @param chatId This is the chat of the receiver.
     * @return true if the file is sent successfully.
     */
    virtual bool sendFile( const QByteArray& file, const QString& fileName, const QVariant& chatId) = 0;

    /**
     * @brief token This is the token value for authentication on the remote server (bot).
     * @return auth token of the bot.
     */
    const QByteArray &token() const;

    /**
     * @brief name This is the name of the bot. Usually this field is received from the server after authentication.
     * @return name of the bot.
     */
    const QString& name() const;

    /**
     * @brief setName This method sets new value for the IBot::name field.
     * @param newName This is new value of the IBot::name property
     */
    void setName(const QString &newName);

    /**
     * @brief takeNextUnreadUpdate This method takes an unread update and marks it as read.
     * @return unread update object. If all updates are read the return nullptr.
     */
    QSharedPointer<iUpdate> takeNextUnreadUpdate();

    /**
     * @brief processed This method returns the list of processed messages.
     * @return list of processed messages.
     */
    QSet<unsigned long long> processed() const;

    /**
     * @brief setProcessed This method sets a new list of processed messages.
     * @param newProcessed list of processed messages.
     */
    virtual void setProcessed(const QSet<unsigned long long> &newProcessed);

    /**
     * @brief reqestLimitPerSecond This is the request performance limitation. By default it is 20 requests per second.
     * @return the maximum number of requests per second.
     */
    int reqestLimitPerSecond() const;

    /**
     * @brief setReqestLimitPerSecond This method sets a new limitation of the bot performance.
     * @param newReqestLimitPerSecond This is the new value of the performance limitation.
     */
    void setReqestLimitPerSecond(int newReqestLimitPerSecond);

    /**
     * @brief parallelActiveNetworkThreads This method returns the number of parallel active network threads.
     * @return the number of parallel active network threads.
     */
    int parallelActiveNetworkThreads() const;

    /**
     * @brief setParallelActiveNetworkThreads This method sets the number of parallel active network threads.
     * @param newParallelActiveNetworkThreads This is the new number of parallel active network threads.
     */
    void setParallelActiveNetworkThreads(int newParallelActiveNetworkThreads);

    /**
     * @brief totalSentRequests This is the total count of prepared requests of the bot from the start.
     * @see startTime method to get the start date time.
     * @return requests count.
     */
    unsigned long long totalSentRequests() const;

    /**
     * @brief startTime This is the time when the bot was started.
     * @return the start date time of the bot.
     */
    QDateTime startTime() const;

protected:

    /**
     * @brief makeMesasge This is a factory method that can create a message type from raw byte data.
     * @param data This is a raw data of the answer.
     * @param args This is the list of arguments of the message.
     * @return message object.
     */
    template<class MessageType, class ... Args>
    static QSharedPointer<MessageType> makeMesasge(const QByteArray& data, Args&& ...args) {
        auto&& ptr = QSharedPointer<MessageType>(new MessageType(std::forward<Args>(args)...));
        ptr->setRawData(data);

        return ptr;
    }

    /**
     * @brief makeMesasge This is a factory method that can create a message type from raw json data.
     * @param data This is a raw json data of the answer.
     * @param args This is the list of arguments of the message.
     * @return message object.
     */
    template<class MessageType, class ... Args>
    static QSharedPointer<MessageType> makeMesasge(const QJsonObject& data, Args&& ...args) {
        auto&& ptr = QSharedPointer<MessageType>(new MessageType(std::forward<Args>(args)...));
        ptr->setRawJson(data);

        return ptr;
    }

    /**
     * @brief makeUrl This method prepares a prefix url for http requests.
     * @param request - This is the request object for which the url will be prepared.
     * @return http request prefix
     */
    virtual QString makeUrl(const QSharedPointer<iRequest>& request) const = 0;

    /**
     * @brief sendRequest This method sends a custom request to the server.
     * @param rquest This is the message that will be sent to the server.
     * @return future pointer to the request replay.
     */
    QFuture<QByteArray>
    sendRequest(const QSharedPointer<iRequest>& rquest);

    /**
     * @brief sendRequest This method sends a custom request to the server.
     * @param rquest This is the message that will be sent to the server.
     * @param pathToResult This is the path to the file where the received data will be saved.
     * @return future pointer to the request replay.
     * @note This is the same as the default implementation except for the save data location,
     *  this method will create a new file located at @a pathToResult and save all received data to this location.
     */
    QFuture<QByteArray>
    sendRequest(const QSharedPointer<iRequest>& rquest, const QString& pathToResult);

    /**
     * @brief setToken This is the setter of the IBot::token value.
     * @param newToken This is the new value of the token.
     */
    void setToken(const QByteArray &newToken);

    /**
     * @brief incomeNewUpdate This method saves incoming messages into the store.
     * @param message This is the new incoming update.
     */
    void incomeNewUpdate(const QSharedPointer<iUpdate>& message);

    /**
     * @brief markMessageAsProcessed This method removes the message from the not processed messages store.
     * @param message This is the message that needs to be processed.
     */
    void markUpdateAsProcessed(const QSharedPointer<iUpdate>& message);

    /**
     * @brief markMessageAsUnprocessed This method adds the message into the not processed messages store.
     * @param message This is the message that needs to be unprocessed.
     * @note this may be useful for processing edited old messages. Just call this method before IBot::incomeNewUpdate.
     */
    void markUpdateAsUnprocessed(const QSharedPointer<iUpdate>& message);

    /**
     * @brief markMessageAsUnprocessed This method adds the message into the not processed messages store.
     * @param messageID This is the id of the message that needs to be unprocessed.
     * @note this may be useful for processing edited old messages. Just call this method before IBot::incomeNewUpdate.
     */
    void markUpdateAsUnprocessed(unsigned long long messageID);

    /**
     * @brief defaultFileStorageLocation This method returns the default file storage location.
     * @return default file storage.
     */
    virtual QString defaultFileStorageLocation() const;

    /**
     * @brief handleIncomeNewUpdate This method just emits the sigReceiveUpdate signal.
     * @note you may override this method to filter the sigReceiveUpdate signal or to handle new updates.
     */
    virtual void handleIncomeNewUpdate(const QSharedPointer<iUpdate>& );
signals:
    /**
     * @brief sigReceiveUpdate emitted when the bot receives any updates from users.
     */
    void sigReceiveUpdate(const QSharedPointer<qTbot::iUpdate>& );

    /**
     * @brief sigStopRequire just a custom event to stop the bot if you use services.
     */
    void sigStopRequire();

private slots:
    void handleEcxecuteRequest();
private:
    unsigned long long makeKey(iRequest::RequestPriority priority);
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
    unsigned long long _totalRequest = 0;
    QDateTime _startTime;
    QMap<unsigned long long, RequestData> _requestQueue;
    int _currentParallelActiveNetworkThreads = 0;
    int _parallelActiveNetworkThreads = 5;

    QRecursiveMutex _mutex;



};

}
#endif // IBOT_H
