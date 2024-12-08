//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "httpexception.h"
#include "ibot.h"
#include "qstandardpaths.h"

#include <QNetworkReply>
#include <QPromise>

namespace qTbot {

IBot::IBot() {
    _manager = new QNetworkAccessManager();
    _manager->setAutoDeleteReplies(true);
}

IBot::~IBot() {
    delete _manager;
}

void IBot::logout() {
    setToken({});
}

const QByteArray &IBot::token() const {
    return _token;
}

void IBot::setToken(const QByteArray &newToken) {
    _token = newToken;
}

void IBot::incomeNewUpdate(const QSharedPointer<iUpdate> &message) {
    if (!message->isValid())
        return;

    auto id = message->updateId();

    if (!_processed.contains(id)) {

        _processed.insert(id);
        _notProcessedUpdates[id] = message;

        handleIncomeNewUpdate(message);
    }
}

QFuture<QByteArray>
IBot::sendRequest(const QSharedPointer<iRequest> &rquest) {

    if (!rquest)
        return {};

    auto && url = makeUrl(rquest);

#ifdef QTBOT_PRINT_RQUESTS
    qDebug() << url;
#endif

    QNetworkReply* networkReplay = nullptr;
    QSharedPointer<QHttpMultiPart> httpData;

    switch (rquest->method()) {
    case iRequest::Get: {
        networkReplay = _manager->get(QNetworkRequest(url));

        break;
    }

    case iRequest::Post:
//        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
//        reply = m_nam.post(req, params.toByteArray());

//        break;
    case iRequest::Upload:
        QNetworkRequest netRequest(url);

        httpData = rquest->argsToMultipartFormData();
        if (httpData) {
            networkReplay = _manager->post(netRequest, httpData.data());

        } else {
            return {};
        }

        break;
    }

    if (!networkReplay) {
        return {};
    }

    auto&& promise = QSharedPointer<QPromise<QByteArray>>::create();

    networkReplay->connect(networkReplay, &QNetworkReply::finished, [promise](){
        promise->finish();
    });

    networkReplay->connect(networkReplay, &QNetworkReply::readyRead, [networkReplay, promise](){
        promise->addResult(networkReplay->readAll());
    });

    networkReplay->connect(networkReplay, &QNetworkReply::errorOccurred, [networkReplay, promise](QNetworkReply::NetworkError ){
        promise->setException(HttpException(networkReplay->error(), networkReplay->errorString().toLatin1()));
        promise->finish();
    });

    auto && setProggress = [promise](qint64 bytesCurrent, qint64 bytesTotal){

        if (promise->future().progressMaximum() != bytesTotal)
            promise->setProgressRange(0, bytesTotal);

        promise->setProgressValue(bytesCurrent);
    };

    networkReplay->connect(networkReplay, &QNetworkReply::downloadProgress, setProggress);
    networkReplay->connect(networkReplay, &QNetworkReply::uploadProgress, setProggress);

    return promise->future();
}

void IBot::markUpdateAsProcessed(const QSharedPointer<iUpdate> &message) {
    _notProcessedUpdates.remove(message->updateId());
}

void IBot::markUpdateAsUnprocessed(const QSharedPointer<iUpdate> &message) {
    return markUpdateAsUnprocessed(message->updateId());
}

void IBot::markUpdateAsUnprocessed(unsigned long long messageID) {
    _processed.remove(messageID);
}

QString IBot::defaultFileStorageLocation() const {
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

void IBot::handleIncomeNewUpdate(const QSharedPointer<iUpdate> & message) {
    emit sigReceiveUpdate(message);
}

QSet<unsigned long long> IBot::processed() const {
    return _processed;
}

void IBot::setProcessed(const QSet<unsigned long long> &newProcessed) {
    _processed = newProcessed;
}

const QString &IBot::name() const {
    return _name;
}

void IBot::setName(const QString &newName) {
    _name = newName;
}

QSharedPointer<iUpdate> IBot::takeNextUnreadUpdate() {
    if (_notProcessedUpdates.size()) {
        auto toRemove = std::move(*_notProcessedUpdates.begin());
        _notProcessedUpdates.erase(_notProcessedUpdates.cbegin());
        return toRemove;
    }

    return nullptr;
}


}
