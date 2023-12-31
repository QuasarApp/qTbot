//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "virtualfile.h"

namespace qTbot {


VirtualFile::VirtualFile(const QSharedPointer<QNetworkReply> &replay): iFile(replay) {
}

const QByteArray& VirtualFile::array() const {
    return _array;
}

iFile::Type VirtualFile::type() const {
    return Type::Ram;
}

void VirtualFile::handleReadReady() {

    _array.append(replay()->readAll());

}

void VirtualFile::handleFinished() {
    handleReadReady();
    iFile::handleFinished();
}

void VirtualFile::handleError(QNetworkReply::NetworkError error) {
    iFile::handleError(error);
    _array.clear();

}

void VirtualFile::setArray(const QByteArray &newArray) {
    _array = newArray;
}


}
