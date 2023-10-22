//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "irequest.h"
#include "qvariant.h"

#include <QBuffer>

namespace qTbot {

iRequest::iRequest()
{

}

QString iRequest::makeUpload() const {

    if (_args.isEmpty() || method() != Get) {
        return "/" + _request;
    }

    return "/" + _request + "?" + argsToUrl();

}

const QMap<QString, QVariant>& iRequest::args() const {
    return _args;
}

void iRequest::addArg(const QString &key, const QVariant &val) {
    _args[key] = val;
}

void iRequest::setArgs(const QMap<QString, QVariant> &newArgs) {
    _args = newArgs;
}

QString iRequest::argsToUrl() const {
    QString args;

    auto it = _args.constBegin();
    while (it != _args.constEnd()) {
        if (args.isEmpty()) {
            args.append(QString("%0=%1").arg(it.key(), it->toString()).toUtf8());
        } else {
            args.append(QString("&%0=%1").arg(it.key(), it->toString()).toUtf8());
        }
        ++it;
    }

    return args;
}

QSharedPointer<QHttpMultiPart> iRequest::argsToMultipartFormData() const {
    QSharedPointer<QHttpMultiPart> multiPart = QSharedPointer<QHttpMultiPart>::create(QHttpMultiPart::FormDataType);

    auto it = _args.constBegin();
    while (it != _args.constEnd()) {
        QHttpPart part;
        auto && value = it.value();

        if (it.key() == REQUEST_UPLOAD_FILE_KEY) {
            QByteArray && array = value.toByteArray();

            const auto metaData = array.split(':');
            if (metaData.size() == 2) {
                const auto fileName = metaData[0];
                const QByteArray fileData = metaData[1];
                part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"document\"; filename=\"" + fileName + "\""));
                part.setBody(fileData);
            } else {
                qWarning() << "the file arguments must be like file:fileName:Data";
                return nullptr;
            }

        } else {
            part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + it.key() + "\""));
            part.setBody(it.value().toByteArray());
        }
        multiPart->append(part);

        ++it;
    }

    return multiPart;
}

const QString& iRequest::request() const {
    return _request;
}

void iRequest::setRequest(const QString &newRequest) {
    _request = newRequest;
}
}
