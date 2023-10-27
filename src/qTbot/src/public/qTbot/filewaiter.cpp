//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "filewaiter.h"
namespace qTbot {

FileWaiter::FileWaiter()
{

}

void FileWaiter::wait(const QSharedPointer<iFile> &file) {
    if (!file->isFinished()) {
        auto address = reinterpret_cast<size_t>(file.get());

        _files[address] = file;


        connect(file.get(), &qTbot::iFile::finishedChanged, this, &FileWaiter::handleFileFinished,
                Qt::QueuedConnection);
    }
}

void FileWaiter::handleFileFinished() {
    auto address = reinterpret_cast<size_t>(sender());

    _files.remove(address);

}

}
