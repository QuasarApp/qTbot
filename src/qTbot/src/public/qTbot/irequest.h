//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IREQUEST_H
#define IREQUEST_H

#include "qTbot/global.h"

#include <QByteArray>
#include <QMap>
#include <QString>
#include <QHttpMultiPart>

#define REQUEST_UPLOAD_FILE_KEY "_file_"

namespace qTbot {

/**
 * @brief ExtraJsonObjects hash map of the extra objects of the message.
 */
typedef QHash<QString, QSharedPointer<QJsonObject>> ExtraJsonObjects;

/**
 * @brief The iRequest class Is main interface for all custom requests.
 * @see IBot::sendRequest
 */
class QTBOT_EXPORT iRequest
{
public:
    /**
     * @brief iRequest default constructor.
     */
    iRequest();

    /**
     * @brief RequestMethod This is the list of supported request types.
     */
    enum RequestMethod {
        /**
         * @brief Get general get request, all request data is sent as a url line.
         */
        Get,
        /**
         * @brief Post general post request.
         */
        Post,
        /**
         * @brief Upload this is a post request to upload big data to telegram.
         */
        Upload
    };

    /**
     * @brief The RequestPriority enum This is the list of request execution priorities on the client side.
     */
    enum RequestPriority {
        /**
         * @brief NoPriority the request has no priority. It will be executed last.
         */
        NoPriority = 0,
        /**
         * @brief LowPriority the request has a low priority.
         */
        LowPriority = 1,
        /**
         * @brief NormalPriority the request has a normal priority. This is the default value.
         */
        NormalPriority = 2,
        /**
         * @brief HighPriority the request has a high priority.
         */
        HighPriority = 3,
        /**
         * @brief UngeredPriority the request has an urgent priority. It will be executed first.
         */
        UngeredPriority = 4,

        /**
         * @brief MaxPriorityValue the maximum value of the priority.
         */
        MaxPriorityValue = 0xff
    };

    /**
     * @brief makeUpload This method prepares the data to upload.
     * @return the data prepared for sending.
     */
    virtual QString makeUpload() const;

    /**
     * @brief baseAddress This method returns the base domain of the remote server.
     * @return base domain name of the remote server.
     */
    virtual QString baseAddress() const = 0;

    /**
     * @brief method returns the method of the request.
     * @return method of the request
     */
    virtual RequestMethod method() const = 0;

    /**
     * @brief request Returns the current request command.
     * @return the current request command.
     */
    const QString& request() const;

    /**
     * @brief setRequest sets a custom request command
     * @param newRequest the new custom command of the request.
     */
    void setRequest(const QString &newRequest);

    /**
     * @brief args This method returns the the current list of arguments
     * @return  the current list of arguments
     */
    const QMap<QString, QVariant> &args() const;

    /**
     * @brief addArg This method pushes a new argument to the arguments list
     * @param key This is the new argument key
     * @param val This is the new argument value.
     */
    void addArg(const QString& key, const QVariant& val);

    /**
     * @brief setArgs For some requests the list of arguments is possible to build only after the constructor.
     * @param newArgs This is the new list of arguments.
     */
    void setArgs(const QMap<QString, QVariant> &newArgs);

    /**
     * @brief argsToUrl
     * This method converts the arguments to a URL string.
     * @return URL string created from the arguments.
     */
    QString argsToUrl() const;

    /**
     * @brief argsToMultipartFormData
     * This method generates multipart/form-data request data.
     *
     * @return QHttpMultiPart - A QHttpMultiPart object containing multipart/form-data request data.
     */
    QSharedPointer<QHttpMultiPart> argsToMultipartFormData() const;

    /**
     * @brief priority This is the priority of executing this request on the client.
     * @return the current request priority.
     */
    RequestPriority priority() const;

    /**
     * @brief setPriority This method sets a new priority for the request.
     * @param newPriority This is the new priority of the request.
     */
    void setPriority(RequestPriority newPriority);

private:
    QString _request;
    QMap<QString, QVariant> _args;
    RequestPriority _priority = RequestPriority::NormalPriority;

};

}
#endif // IREQUEST_H
