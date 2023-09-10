//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "telegramsinglerquest.h"


namespace qTbot {

TelegramSingleRquest::TelegramSingleRquest(QByteArray&& request, QMap<QString, QVariant>&& args) {
    _request = std::move(request);
    _args = std::move(args);
}

QByteArray TelegramSingleRquest::makeUpload() const {

    if (_args.isEmpty()) {
        return "/" + _request;
    }

    QByteArray args;

    auto it = _args.constBegin();
    while (it != _args.constEnd()) {
        if (args.isEmpty()) {
            args.append(QString("%1=%2").arg((it.key(), it->toString())).toUtf8());
        } else {
            args.append(QString("&%1=%2").arg((it.key(), it->toString())).toUtf8());
        }
        ++it;
    }

    return "/" + _request + "?" + args;

}

}