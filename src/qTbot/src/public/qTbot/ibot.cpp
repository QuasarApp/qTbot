//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ibot.h"
#include "qstandardpaths.h"

#include <QNetworkReply>

namespace qTbot {

IBot::IBot() {
    _manager = new QNetworkAccessManager();
    _manager->setAutoDeleteReplies(false);
}

IBot::~IBot() {
    delete _manager;
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

QSharedPointer<QNetworkReply>
IBot::sendRequest(const QSharedPointer<iRequest> &rquest) {
    if (!rquest)
        return nullptr;

    doRemoveFinishedRequests();

    auto && url = makeUrl(rquest);

#ifdef QTBOT_PRINT_RQUESTS
    qDebug() << url;
#endif

    QSharedPointer<QNetworkReply> networkReplay;
    QSharedPointer<QHttpMultiPart> httpData;

    switch (rquest->method()) {
    case iRequest::Get:
        networkReplay.reset(_manager->get(QNetworkRequest(url)));
        break;
    case iRequest::Post:
//        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
//        reply = m_nam.post(req, params.toByteArray());

//        break;
    case iRequest::Upload:
        QNetworkRequest netRequest(url);
        netRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("multipart/form-data"));

        httpData = rquest->argsToMultipartFormData();
        if (httpData) {
            networkReplay.reset(_manager->post(netRequest, httpData.data()));
        } else {
            return nullptr;
        }

        break;
    }

    size_t address = reinterpret_cast<size_t>(networkReplay.get());
    _replayStorage[address] = networkReplay;

    connect(networkReplay.get(), &QNetworkReply::finished, this,
            [this, address, httpData]() {
                _toRemove.push_back(address);
            });

    connect(networkReplay.get(), &QNetworkReply::errorOccurred, this,
            [this, address](QNetworkReply::NetworkError err){
                qWarning() << "The reqeust " << address << " finished with error code : " << err;
                if (auto&& replay = _replayStorage.value(address)) {
                    qWarning() << "Server ansver: " << replay->readAll() << "request: ";
                    auto request = replay->request();
                    QUrl url = request.url();
                    qDebug() << "URL: " << url.toString();

                    QList<QByteArray> headers = request.rawHeaderList();
                    qDebug() << "rquest headers:";
                    foreach (QByteArray header, headers) {
                        qDebug() << header << ": " << request.rawHeader(header);
                    }
                }

                _toRemove.push_back(address);
            });

    return networkReplay;
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

void IBot::doRemoveFinishedRequests() {
    for (auto address: qAsConst(_toRemove)) {
        _replayStorage.remove(address);
    }

    _toRemove.clear();
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
