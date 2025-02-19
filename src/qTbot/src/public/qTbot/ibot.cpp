//#
//# Copyright (C) 2023-2025 QuasarApp.
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
    _requestExecutor = new QTimer(this);
    _requestExecutor->setInterval(1000 / 20); // 20 times per second.

    connect(_requestExecutor, &QTimer::timeout, this , &IBot::handleEcxecuteRequest);
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
    _startTime = QDateTime::currentDateTime();

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

QNetworkReply* IBot::sendRquestImpl(const QSharedPointer<iRequest> &rquest) {
    if (!rquest)
        return {};

    auto && url = makeUrl(rquest);

#ifdef QTBOT_PRINT_RQUESTS
    qDebug() << url;
#endif

    QNetworkReply* networkReplay = nullptr;

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

        auto httpData = rquest->argsToMultipartFormData();
        if (httpData) {
            networkReplay = _manager->post(netRequest, httpData.data());
            connect(networkReplay, &QNetworkReply::destroyed, [httpData](){});

        } else {
            return {};
        }

        break;
    }

    return networkReplay;
}

QDateTime IBot::startTime() const {
    return _startTime;
}

unsigned long long IBot::totalSentRequests() const {
    return _totalRequest;
}

int IBot::parallelActiveNetworkThreads() const {
    return _parallelActiveNetworkThreads;
}

void IBot::setParallelActiveNetworkThreads(int newParallelActiveNetworkThreads) {
    _parallelActiveNetworkThreads = newParallelActiveNetworkThreads;
}

void IBot::setCurrentParallelActiveNetworkThreads(int newParallelActiveNetworkThreads) {
    bool wasBusy = _currentParallelActiveNetworkThreads == _parallelActiveNetworkThreads;
    static bool lastMessageWasFree = false;

    _currentParallelActiveNetworkThreads = newParallelActiveNetworkThreads;

    if (_currentParallelActiveNetworkThreads == _parallelActiveNetworkThreads) {
        qInfo() << "All network threads are busy!";
        lastMessageWasFree = false;

    } else if (wasBusy) {
        qInfo() << "Network threads are free! available: " << _currentParallelActiveNetworkThreads << " from " << _parallelActiveNetworkThreads;
        lastMessageWasFree = false;

    } else if (_currentParallelActiveNetworkThreads == 0 && !lastMessageWasFree) {
        qInfo() << "All network threads are free!";
        lastMessageWasFree = true;
    }
}

int IBot::reqestLimitPerSecond() const {
    return _requestExecutor->interval() * 1000;
}

void IBot::setReqestLimitPerSecond(int newReqestLimitPerSecond) {
    _requestExecutor->setInterval(1000 / newReqestLimitPerSecond);
}

QFuture<QByteArray>
IBot::sendRequest(const QSharedPointer<iRequest> &rquest) {
    auto&& responce = QSharedPointer<QPromise<QByteArray>>::create();
    responce->start();

    {
        QMutexLocker lock(&_mutex);
        _requestQueue.insert(makeKey(rquest->priority()),
                             RequestData{rquest, "", responce});
    }

    if (!_requestExecutor->isActive()) {
        handleEcxecuteRequest();
        _requestExecutor->start();

    }

    return responce->future();
}

QFuture<QByteArray>
IBot::sendRequest(const QSharedPointer<iRequest> &rquest,
                  const QString &pathToResult) {
    auto&& responce = QSharedPointer<QPromise<QByteArray>>::create();
    responce->start();

    {
        QMutexLocker lock(&_mutex);
        _requestQueue.insert(makeKey(rquest->priority()),
                             RequestData{rquest, pathToResult, responce});
    }


    if (!_requestExecutor->isActive()) {
        handleEcxecuteRequest();
        _requestExecutor->start();

    }

    return responce->future();

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

void IBot::handleEcxecuteRequest() {
    QMutexLocker lock(&_mutex);

    if (!_requestQueue.size()) {
        _requestExecutor->stop();
        return;
    }

    if (_currentParallelActiveNetworkThreads > _parallelActiveNetworkThreads) {
        return;
    }

    auto&& requestData = _requestQueue.take(_requestQueue.firstKey());

    if (requestData.responceFilePath.size()) {
        sendRequestPrivate(requestData.request, requestData.responceFilePath, requestData.responce);
        return;
    }

    sendRequestPrivate(requestData.request, requestData.responce);
}

unsigned long long IBot::makeKey(iRequest::RequestPriority priority) {
    unsigned long long key = _totalRequest;
    _totalRequest++;
    key = key | (static_cast<unsigned long long>(iRequest::RequestPriority::MaxPriorityValue - priority) << 56);
    return key;
}

void IBot::sendRequestPrivate(const QSharedPointer<iRequest> &rquest,
                              const QSharedPointer<QPromise<QByteArray> > &promise) {

    QNetworkReply* networkReplay = sendRquestImpl(rquest);
    if (!networkReplay) {
        return;
    }

    setCurrentParallelActiveNetworkThreads(_currentParallelActiveNetworkThreads + 1);

    connect(networkReplay, &QNetworkReply::finished, [this, networkReplay, promise](){
        if (networkReplay->error() == QNetworkReply::NoError) {
            promise->addResult(networkReplay->readAll());
            promise->finish();

        } else {
            QByteArray msg = networkReplay->errorString().toLatin1() + networkReplay->readAll();
            promise->setException(HttpException(networkReplay->error(), msg));
#ifdef QTBOT_PRINT_ERRORS
            qCritical() << msg;
#endif

        }

        setCurrentParallelActiveNetworkThreads(_currentParallelActiveNetworkThreads - 1);

    });

    auto && setProggress = [promise](qint64 bytesCurrent, qint64 bytesTotal){

        if (promise->future().progressMaximum() != bytesTotal)
            promise->setProgressRange(0, bytesTotal);

        promise->setProgressValue(bytesCurrent);
    };

    connect(networkReplay, &QNetworkReply::downloadProgress, setProggress);
    connect(networkReplay, &QNetworkReply::uploadProgress, setProggress);
}

void IBot::sendRequestPrivate(const QSharedPointer<iRequest> &rquest,
                              const QString &pathToResult,
                              const QSharedPointer<QPromise<QByteArray>> & promise) {
    auto&& file = QSharedPointer<QFile>::create(pathToResult);

    if (!file->open(QIODeviceBase::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Fail to wrote data into " << pathToResult;
        return;
    }

    QNetworkReply* networkReplay = sendRquestImpl(rquest);
    if (!networkReplay) {
        return;
    }

    setCurrentParallelActiveNetworkThreads(_currentParallelActiveNetworkThreads + 1);
    connect(networkReplay, &QNetworkReply::finished, [this, promise, networkReplay, pathToResult](){

        if (networkReplay->error() == QNetworkReply::NoError) {
            QByteArray msg = networkReplay->errorString().toLatin1();
            promise->setException(HttpException(networkReplay->error(), msg));
#ifdef QTBOT_PRINT_ERRORS
            qCritical() << msg;
#endif
        } else {
            promise->addResult(pathToResult.toUtf8()); // wil not work with UTF 8 path names
            promise->finish();
        }
        setCurrentParallelActiveNetworkThreads(_currentParallelActiveNetworkThreads - 1);
    });

    connect(networkReplay, &QNetworkReply::readyRead, [networkReplay, promise, pathToResult, file](){
        if (networkReplay->error() == QNetworkReply::NoError) {
            file->write(networkReplay->readAll());
        }

    });

    auto && setProggress = [promise](qint64 bytesCurrent, qint64 bytesTotal){

        if (promise->future().progressMaximum() != bytesTotal)
            promise->setProgressRange(0, bytesTotal);

        promise->setProgressValue(bytesCurrent);
    };

    connect(networkReplay, &QNetworkReply::downloadProgress, setProggress);
    connect(networkReplay, &QNetworkReply::uploadProgress, setProggress);

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
