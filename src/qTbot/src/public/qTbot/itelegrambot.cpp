//#
//# Copyright (C) 2018-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "itelegrambot.h"
#include <QNetworkAccessManager>

#include <qTbot/messages/telegramgetmsg.h>

#include <QNetworkReply>
#include <QSharedPointer>

namespace qTbot {

ITelegramBot::ITelegramBot() {
    _manager = new QNetworkAccessManager();
}

ITelegramBot::~ITelegramBot() {
    delete _manager;
}

bool ITelegramBot::login(const QByteArray &token) {
    if (token.isEmpty()) {
        return false;
    }

    setToken(token);

    return sendMessage(QSharedPointer<TelegramGetMsg>::create());
}

bool ITelegramBot::sendMessage(const QSharedPointer<iMessage> &message) {
    if (!message)
        return false;

    auto getInfoRquest = makePrefix() + message->makeUpload();

    QNetworkReply* networkReplay = _manager->get(QNetworkRequest(QUrl::fromEncoded(getInfoRquest)));

    if (!networkReplay)
        return false;

    connect(networkReplay, &QNetworkReply::finished,
            this, &ITelegramBot::handleReplayIsFinished,
            Qt::QueuedConnection);

    return true;
}

QByteArray ITelegramBot::makePrefix() const {
    return "https://api.telegram.org/bot" + token();
}

void ITelegramBot::handleReplayIsFinished() {
    if (QNetworkReply* replay =  dynamic_cast<QNetworkReply*>(sender())) {

        auto rawData = replay->readAll();

        auto message = QSharedPointer<ITelegramMessage>::create();
        message->setRawData(rawData);

        replay->deleteLater();

        onMessageReceived(message);

        emit receiveMessage(message);
    }
}

}
