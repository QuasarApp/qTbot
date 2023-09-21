//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef VIRTUALFILE_H
#define VIRTUALFILE_H

#include "ifile.h"

namespace qTbot {

/**
 * @brief The VirtualFile class write and read data from the Ram.
 */
class  QTBOT_EXPORT VirtualFile : public iFile
{
public:
    VirtualFile(const QSharedPointer<QNetworkReply>& replay,
                const QWeakPointer<QByteArray> &array);

    // iFile interface
    const QWeakPointer<QByteArray>& array() const;
    Type type() const override;

protected slots:
    void handleReadReady() override;
    void handleFinished() override;
    void handleError(QNetworkReply::NetworkError error) override;

private:
    QWeakPointer<QByteArray> _array;
};

}
#endif // VIRTUALFILE_H
