//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "replaydata.h"



namespace qTbot {

ReplayData::ReplayData() { }
ReplayData::ReplayData(const QSharedPointer<QNetworkReply> &newReplay) {

    replay = newReplay;


    QObject::connect(replay.get(), &QNetworkReply::downloadProgress,
                     [this](qint64 bytesReceived, qint64 bytesTotal){
        setDownloadProgress(bytesTotal / static_cast<float>(bytesReceived));
    }); // clazy-connect-3arg-lambda

    // connect-3arg-lambda
    QObject::connect(replay.get(), &QNetworkReply::uploadProgress, [this](qint64 bytesSent, qint64 bytesTotal){
        setUploadProgress(bytesTotal / static_cast<float>(bytesSent));
    });
}

const QSharedPointer<QNetworkReply>& ReplayData::getReplay() const {
    return replay;
}

const QSharedPointer<QNetworkReply> &ReplayData::getReplay() {
    return replay;
}

float ReplayData::getUploadProgress() const {
    return uploadProgress;
}

void ReplayData::setUploadProgress(float newUploadProgress) {
    uploadProgress = newUploadProgress;
}

float ReplayData::getDownloadProgress() const {
    return downloadProgress;
}

void ReplayData::setDownloadProgress(float newDownloadProgress) {
    downloadProgress = newDownloadProgress;
}

}
