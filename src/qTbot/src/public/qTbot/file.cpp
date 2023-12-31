//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "file.h"

namespace qTbot {


File::File(const QSharedPointer<QNetworkReply> &replay, const QString &filePath): iFile(replay) {
    _localFile.setFileName(filePath);

    if (!_localFile.isOpen()) {
        _localFile.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Append);
    }

}

File::File(const QString &filePath):File(nullptr, filePath) {

}

const QFile & File::localFile() const {
    return _localFile;
}

iFile::Type File::type() const {
    return Type::Local;
}

void File::handleReadReady() {
    auto&& bytes = replay()->readAll();

    if (bytes.size()) {
        _localFile.write(bytes);
        _localFile.flush();
    }
}

void File::handleFinished() {
    handleReadReady();
    _localFile.close();
    iFile::handleFinished();
}

void File::handleError(QNetworkReply::NetworkError error) {
    iFile::handleError(error);
    _localFile.close();

    _localFile.remove();
}

}
