//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramsendfile.h"

#include <QJsonDocument>

namespace qTbot {


qTbot::TelegramSendFile::TelegramSendFile(const QString &request,
                                          const QString &fileName,
                                          const QString &fileType,
                                          const QByteArray& data,
                                          const TelegramArgs &args,
                                          const ExtraJsonObjects& extraObjects
                                          ):
    TelegramSingleRquest(request, args.toMap(true)) {
    setPriority(args.requestPriority);


    for (auto it = extraObjects.begin(); it != extraObjects.end(); it = std::next(it)) {
        addArg(it.key(), QJsonDocument(*it.value()).toJson(QJsonDocument::Compact));
    }

    addArg(QString("%0:%1:%2").arg(REQUEST_UPLOAD_FILE_KEY, fileName, fileType), data);
}

qTbot::TelegramSendFile::TelegramSendFile(const QString &request,
                                          const QFileInfo &file,
                                          const TelegramArgs &args,
                                          const QHash<QString, QSharedPointer<QJsonObject> > &extraObjects):
    TelegramSingleRquest(request, args.toMap(true)) {
    setPriority(args.requestPriority);

    QFile readFile(file.absoluteFilePath());
    if (!readFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Fail to open file" << file.absoluteFilePath();
    }

    for (auto it = extraObjects.begin(); it != extraObjects.end(); it = std::next(it)) {
        addArg(it.key(), QJsonDocument(*it.value()).toJson(QJsonDocument::Compact));
    }

    auto&& sufix = file.suffix();
    if (sufix.contains("png") || sufix.contains("jpg") || sufix.contains("jepg") || sufix.contains("gif")) {
        addArg(QString("%0:%1:%2").arg(REQUEST_UPLOAD_FILE_KEY, file.fileName(), TELEGRAM_PHOTO),  readFile.readAll());

    } else {
        addArg(QString("%0:%1:%2").arg(REQUEST_UPLOAD_FILE_KEY, file.fileName(), TELEGRAM_DOCUMENT), readFile.readAll());

    }

    readFile.close();
}

iRequest::RequestMethod TelegramSendFile::method() const {
    return iRequest::RequestMethod::Upload;
}

QString TelegramSendFile::type() const {
    return REQUEST_UPLOAD_FILE_KEY;
}
}
