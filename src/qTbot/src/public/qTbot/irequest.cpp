//#
//# Copyright (C) 2023-2026 QuasarApp.
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

        if (it.key().contains(REQUEST_UPLOAD_FILE_KEY)) {
            auto metaData = it.key().split(":");

            if (metaData.size() == 3) {
                const auto fileName = metaData[1];
                const auto fileType = metaData[2];

                part.setHeader(QNetworkRequest::ContentDispositionHeader,
                               "form-data; name=\"" + fileType + "\"; filename=\"" + fileName + "\"");

                part.setBody(value.toByteArray());
            } else {
                qWarning() << "the file arguments must be like _file_:fileName:fileType" << _args;
                return nullptr;
            }

        } else {
            part.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"" + it.key() + "\"");
            part.setBody(value.toByteArray());
        }
        multiPart->append(part);

        ++it;
    }

    return multiPart;
}

iRequest::RequestPriority iRequest::priority() const {
    return _priority;
}

void iRequest::setPriority(RequestPriority newPriority) {
    _priority = newPriority;
}

const QString& iRequest::request() const {
    return _request;
}

void iRequest::setRequest(const QString &newRequest) {
    _request = newRequest;
}
}
