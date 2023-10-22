//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IFILE_H
#define IFILE_H

#include "qnetworkreply.h"
#include <qTbot/global.h>
#include <QFile>

namespace qTbot {

/**
 * @brief The iFile class This is main interface for all implementations of the files.
 */
class QTBOT_EXPORT iFile: public QObject
{
    Q_OBJECT
public:

    /**
     * @brief The Type enum is type of the file object.
     */
    enum Type {
        /// This is local file, all receive bytes will be save directed into file.
        Local,
        /// This is memory saved file. All received bytes will be saved into QByteArray object.
        Ram
    };

    iFile(const QSharedPointer<QNetworkReply>& replay);

    /**
     * @brief Get the current upload progress.
     * @return The current upload progress as a floating-point value.
     */
    float uploadProgress() const;

    /**
     * @brief Set the upload progress.
     * @param newUploadProgress The new upload progress value to set.
     */
    void setUploadProgress(float newUploadProgress);

    /**
     * @brief Get the current download progress.
     * @return The current download progress as a floating-point value.
     */
    float downloadProgress() const;

    /**
     * @brief Set the download progress.
     * @param newDownloadProgress The new download progress value to set.
     */
    void setDownloadProgress(float newDownloadProgress);

    /**
     * @brief Get the error code associated with this file.
     * @return The error code as an integer value.
     */
    int error() const;

    /**
     * @brief Set the error code for this file.
     * @param newError The new error code to set.
     */
    void setError(int newError);

    /**
     * @brief Get the shared pointer to the associated QNetworkReply.
     * @return A shared pointer to the associated QNetworkReply.
     */
    const QSharedPointer<QNetworkReply>& replay() const;

    /**
     * @brief type This is type of the file object.
     * @return type of the file object.
     */
    virtual Type type() const = 0;

    /**
     * @brief finished return true if the request was finished else false.
     * @return true if the request was finished else false
     */
    bool isFinished() const;

    /**
     * @brief setDownloadRequest This method sets replay for the file.
     * @param replay This is pointer to the replay.
     */
    void setDownloadRequest(const QSharedPointer<QNetworkReply>& replay);
protected:

    /**
     * @brief setFinished monual sets finished flag.
     * @param newFinished new value for the finished flag.
     */
    void setFinished(bool newFinished);

protected slots:
    /**
     * @brief Slot to handle when data is ready to be read.
     */
    virtual void handleReadReady() = 0;

    /**
     * @brief Slot to handle when the network operation is finished.
     */
    virtual void handleFinished();

    /**
     * @brief Slot to handle errors in the network operation.
     * @param error This is error code.
     */
    virtual void handleError(QNetworkReply::NetworkError error);

private slots:

    /**
     * @brief Slot to handle changes in upload progress.
     * @param bytesSent current snet bytes.
     * @param bytesTotal total to sent bytes.
     */
    void handleUploadProgressChanged(qint64 bytesSent, qint64 bytesTotal);

    /**
     * @brief Slot to handle changes in download progress.
     * @param bytesReceived current received bytes.
     * @param bytesTotal total to receive bytes.
     */
    void handleDownloadProgressChanged(qint64 bytesReceived, qint64 bytesTotal);

signals:
    /**
     * @brief Signal emitted when the upload progress changes.
     */
    void uploadProgressChanged();

    /**
     * @brief Signal emitted when the download progress changes.
     */
    void downloadProgressChanged();

    /**
     * @brief Signal emitted when the error code changes.
     */
    void errorChanged();

    /**
     * @brief Signal emitted when the associated QNetworkReply changes.
     */
    void replayChanged();

    /**
     * @brief Signal emitted when the associated finished changes.
     */
    void finishedChanged();

private:
    float _uploadProgress = 0;
    float _downloadProgress = 0;
    int _error = 0;
    bool _finished = false;

    QSharedPointer<QNetworkReply> _replay;

    friend class ITelegramBot;
};
}
#endif // IFILE_H
