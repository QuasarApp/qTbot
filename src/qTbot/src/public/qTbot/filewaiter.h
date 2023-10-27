//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef FILEWAITER_H
#define FILEWAITER_H

#include "ifile.h"

namespace qTbot {

/**
 * @brief The FileWaiter class. This is a simple storage for the shared pointer of files.
 * All added files will be removed (shared object) after finish donwload or upload.
 */
class FileWaiter: public QObject
{
    Q_OBJECT
public:
    FileWaiter();

    /**
     * @brief wait This method add shared pointer of file in to local storage, and remove it from this when @a file change state to finish.
     * @param file This is a processed file.
     * @note The file will not added if the file alredey finished.
     * @note This method not stop thread, it is just save a file until it is is progres
     */
    void wait(const QSharedPointer<iFile>& file);

private slots:
    void handleFileFinished();

private:
    QHash<size_t, QSharedPointer<iFile>> _files;


};
}
#endif // FILEWAITER_H
