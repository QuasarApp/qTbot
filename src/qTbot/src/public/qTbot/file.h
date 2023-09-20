//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef FILE_H
#define FILE_H

#include "ifile.h"

namespace qTbot {

/**
 * @brief The File class is implementations for local files.
 */
class QTBOT_EXPORT File: public iFile
{
    Q_OBJECT
public:
    File(const QSharedPointer<QNetworkReply>& replay, const QString &filePath);

    const QFile & localFile() const;


    // iFile interface
protected slots:
    void handleReadReady() override;
    void handleFinished() override;
    void handleError(QNetworkReply::NetworkError error) override;
private:
    QFile _localFile;

};
}
#endif // FILE_H
