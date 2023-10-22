//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#
#include "telegramsenddocument.h"

namespace qTbot {

TelegramSendDocument::TelegramSendDocument(const QVariant &chatId,
                                           const QString &text,
                                           const QString& fileName,
                                           const QByteArray &data):
    TelegramSingleRquest("sendDocument") {

    addArg("chat_id", chatId);
    if (text.size())
        addArg("caption", text);

    addArg(QString("%0:%1").arg(REQUEST_UPLOAD_FILE_KEY, fileName), data);

}

TelegramSendDocument::TelegramSendDocument(const QVariant &chatId,
                                           const QString &text,
                                           const QFileInfo &file):
    TelegramSingleRquest("sendDocument")
{
    addArg("chat_id", chatId);

    if (text.size())
        addArg("text", text);

    QFile readFile(file.absoluteFilePath());
    if (!readFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Fail to open file" << file.absoluteFilePath();
    }

    addArg(REQUEST_UPLOAD_FILE_KEY, file.completeBaseName().toLatin1() + ":" + readFile.readAll());
}

iRequest::RequestMethod TelegramSendDocument::method() const {
    return Upload;
}
}
