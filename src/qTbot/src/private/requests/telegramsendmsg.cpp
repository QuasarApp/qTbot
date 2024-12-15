//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramsendmsg.h"

#include <QJsonDocument>
#include <QJsonObject>
namespace qTbot {

TelegramSendMsg::TelegramSendMsg(const TelegramArgs& generalArgs,
                                 const QHash<QString, QSharedPointer<QJsonObject> > &extraObjects)
                                 :
    TelegramSingleRquest("sendMessage")
{

    QMap<QString, QVariant>&& args = generalArgs.toMap();
    setPriority(generalArgs.requestPriority);

    for (auto it = extraObjects.begin(); it != extraObjects.end(); it = std::next(it)) {
        args[it.key()] = QJsonDocument(*it.value()).toJson(QJsonDocument::Compact);
    }

    setArgs(args);
}
}
