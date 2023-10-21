//#
//# Copyright (C) 2023-2023 QuasarApp.
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

namespace qTbot {

/**
 * @brief The iRequest class Is main interface for all custom requests.
 * @see IBot::sendRequest
 */
class QTBOT_EXPORT iRequest
{
public:
    iRequest();

    /**
     * @brief RequestMethod Tgis islist of supported requests types of the requests.
     */
    enum RequestMethod {
        /// general ger request, all request data sent as a url line
        Get,
        /// general post request
        Post,
        /// this is post request to upload a big data to telegram
        Upload
    };

    /**
     * @brief makeUpload This method prepare data to upload;
     * @return data array prepared to sending.
     */
    virtual QString makeUpload() const;

    /**
     * @brief baseAddress This method return base domain of remote server.
     * @return base domain name of remoute server.
     */
    virtual QString baseAddress() const = 0;

    /**
     * @brief method returns method of the request.
     * @return method of the request
     */
    virtual RequestMethod method() const = 0;

    /**
     * @brief request return current requests commnad.
     * @return current requests commnad.
     */
    const QString& request() const;

    /**
     * @brief setRequest sets custom requests commnad
     * @param newRequest new custom commnad of the request.
     */
    void setRequest(const QString &newRequest);

    /**
     * @brief args This method returns a current list of arguments
     * @return  current list of arguments
     */
    const QMap<QString, QVariant> &args() const;

    /**
     * @brief addArg This method push new arg, to arguments list
     * @param key This is new argument key
     * @param val this is new argument value.
     */
    void addArg(const QString& key, const QVariant& val);

    /**
     * @brief setArgs For the some requests list of arguments posible to build only after constructor.
     * @param newArgs This is new list of arguments.
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
    QHttpMultiPart argsToMultipartFormData() const;
private:
    QString _request;
    QMap<QString, QVariant> _args;

};

}
#endif // IREQUEST_H
