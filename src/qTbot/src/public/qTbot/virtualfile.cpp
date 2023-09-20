//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "virtualfile.h"

namespace qTbot {


VirtualFile::VirtualFile(const QSharedPointer<QNetworkReply> &replay,
                         const QWeakPointer<QByteArray> &array): iFile(replay) {
    _array = array;
}

const QWeakPointer<QByteArray>& VirtualFile::array() const {
    return _array;
}

void VirtualFile::handleReadReady() {

    if (auto&& strongArray = _array.lock()) {
        strongArray->append(replay()->readAll());
    }
}

void VirtualFile::handleFinished() {
    handleReadReady();

}

void VirtualFile::handleError(QNetworkReply::NetworkError error) {
    iFile::handleError(error);
    _array.clear();

}


}
