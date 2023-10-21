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

QHttpMultiPart iRequest::argsToMultipartFormData() const {
    QHttpMultiPart multiPart(QHttpMultiPart::FormDataType);

    auto it = _args.constBegin();
    while (it != _args.constEnd()) {
        QHttpPart part;
        auto && value = it.value();
        if (value.typeId() == QMetaType::QByteArray) {
            QByteArray && array = value.toByteArray();

            if (array.left(5) == "file:") {
                const auto metaData = array.split(':');
                if (metaData.size() == 3) {
                    const auto fileName = metaData[1];
                    const QByteArray fileData = metaData[2];
                    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"document\"; filename=\"" + fileName + "\""));
                    part.setBody(fileData);
                } else {
                    qWarning() << "the file arguments must be like file:fileName:Data";
                }

            } else {
                part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + it.key() + "\""));
                part.setBody(it.value().toByteArray());
            }
        }
        multiPart.append(part);

        ++it;
    }
    multiPart.append(chatIdPart);
}

const QString& iRequest::request() const {
    return _request;
}

void iRequest::setRequest(const QString &newRequest) {
    _request = newRequest;
}
}
