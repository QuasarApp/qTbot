//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef REPLAYDATA_H
#define REPLAYDATA_H

#include "QNetworkReply"
namespace qTbot {

/**
 * @brief The ReplayData class This is wraper of the QNetworReplay with progress inforamtion. used in the iBot class.
 */
class ReplayData
{
public:
    ReplayData();
    ReplayData(const QSharedPointer<QNetworkReply>& newReplay);


    const QSharedPointer<QNetworkReply>& getReplay() const;
    const QSharedPointer<QNetworkReply>& getReplay();

    float getUploadProgress() const;
    void setUploadProgress(float newUploadProgress);

    float getDownloadProgress() const;
    void setDownloadProgress(float newDownloadProgress);

private:

    float uploadProgress = 0;
    float downloadProgress = 0;

    QSharedPointer<QNetworkReply> replay;

};

}
#endif // REPLAYDATA_H
