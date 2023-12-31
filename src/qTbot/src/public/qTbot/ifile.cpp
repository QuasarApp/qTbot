//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ifile.h"

namespace qTbot {

iFile::iFile(const QSharedPointer<QNetworkReply>& replay) {
    setDownloadRequest(replay);
}

float iFile::uploadProgress() const {
    return _uploadProgress;
}

void iFile::setUploadProgress(float newUploadProgress) {
    if (qFuzzyCompare(_uploadProgress, newUploadProgress))
        return;

    _uploadProgress = newUploadProgress;
    emit uploadProgressChanged();
}

float iFile::downloadProgress() const {
    return _downloadProgress;
}

void iFile::setDownloadProgress(float newDownloadProgress) {
    if (qFuzzyCompare(_downloadProgress, newDownloadProgress))
        return;

    _downloadProgress = newDownloadProgress;
    emit downloadProgressChanged();
}

int iFile::error() const {
    return _error;
}

void iFile::setError(int newError) {
    if (_error == newError)
        return;
    _error = newError;
    emit errorChanged();
}

const QSharedPointer<QNetworkReply> &iFile::replay() const {
    return _replay;
}

bool iFile::isFinished() const {
    return _finished;
}

void iFile::handleError(QNetworkReply::NetworkError error) {
    setError(error);
    setUploadProgress(0);
    setDownloadProgress(0);

}

void iFile::handleUploadProgressChanged(qint64 bytesSent, qint64 bytesTotal) {
    setUploadProgress(bytesSent / static_cast<float>(bytesTotal));
}

void iFile::handleDownloadProgressChanged(qint64 bytesReceived, qint64 bytesTotal) {
    setDownloadProgress(bytesReceived / static_cast<float>(bytesTotal));
}

void iFile::setDownloadRequest(const QSharedPointer<QNetworkReply> &replay) {

    if (_replay) {
        disconnect(_replay.get(), &QNetworkReply::finished,
                   this, &iFile::handleFinished);

        disconnect(_replay.get(), &QNetworkReply::errorOccurred,
                   this, &iFile::handleError);

        disconnect(_replay.get(), &QNetworkReply::readyRead,
                   this, &iFile::handleReadReady);

        disconnect(_replay.get(), &QNetworkReply::uploadProgress,
                   this, &iFile::handleUploadProgressChanged);

        disconnect(_replay.get(), &QNetworkReply::downloadProgress,
                   this, &iFile::handleDownloadProgressChanged);
    }

    _replay = replay;

    if (_replay) {
        connect(replay.get(), &QNetworkReply::finished,
                this, &iFile::handleFinished, Qt::DirectConnection);

        connect(replay.get(), &QNetworkReply::errorOccurred,
                this, &iFile::handleError, Qt::DirectConnection);

        connect(replay.get(), &QNetworkReply::readyRead,
                this, &iFile::handleReadReady, Qt::DirectConnection);

        connect(replay.get(), &QNetworkReply::uploadProgress,
                this, &iFile::handleUploadProgressChanged, Qt::DirectConnection);

        connect(replay.get(), &QNetworkReply::downloadProgress,
                this, &iFile::handleDownloadProgressChanged, Qt::DirectConnection);
    }

}

void iFile::setFinished(bool newFinished) {

    if (newFinished != _finished) {
        _finished = newFinished;
        emit finishedChanged();
    }
}

void iFile::handleFinished() {
    setFinished(true);
}
}
