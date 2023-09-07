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
#include <QDebug>

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

    ITelegramBot::Responce cb = [this]( const QSharedPointer<iRequest>& ,
                                       const QSharedPointer<iMessage>& responce,
                                       int err) {

        if (err) {
            qDebug() << "Network error occured. code: " << err;
        }

        if (auto message = responce.dynamicCast<ITelegramMessage>()) {
            setId(message->rawJson().value("id").toInt());
            setName(message->rawJson().value("first_name").toString());
            setUsername(message->rawJson().value("username").toString());
        }
    };

    return sendRequest(QSharedPointer<TelegramGetMsg>::create(), cb);
}

bool ITelegramBot::sendMessage(const QSharedPointer<iMessage> &message) {
    if (!message)
        return false;

    auto getInfoRquest = makePrefix() + message->makeUpload();

    QNetworkReply* networkReplay = _manager->get(QNetworkRequest(QUrl::fromEncoded(getInfoRquest)));

    if (!networkReplay)
        return false;

    return true;
}

QByteArray ITelegramBot::makePrefix() const {
    return "https://api.telegram.org/bot" + token();
}

bool ITelegramBot::sendRequest(const QSharedPointer<iRequest> &rquest, const Responce &cb) {
    if (!rquest)
        return false;


    auto getInfoRquest = makePrefix() + rquest->makeUpload();

    QNetworkReply* networkReplay = _manager->get(QNetworkRequest(QUrl::fromEncoded(getInfoRquest)));
    if (!networkReplay)
        return false;

    auto handler = [rquest, cb, networkReplay]() {

        auto rawData = networkReplay->readAll();

        auto message = QSharedPointer<ITelegramMessage>::create();
        message->setRawData(rawData);

        if (!message->isValid()) {
            qDebug() << "Some request is wrong: code:" << message->rawJson().value("error_code").toInt();
            qDebug() << "What: " << message->rawJson().value("description").toString();

            return;
        }

        networkReplay->deleteLater();

        if (cb) {
            cb(rquest, message, 0);
        }
    };

    auto err = [rquest, cb, networkReplay](QNetworkReply::NetworkError err) {

        networkReplay->deleteLater();

        if (cb) {
            cb(rquest, nullptr, err);
        }
    };

    connect(networkReplay, &QNetworkReply::finished, handler);
    connect(networkReplay, &QNetworkReply::errorOccurred, err);

    return true;
}

void ITelegramBot::setUsername(const QString &newUsername) {
    _username = newUsername;
}

void ITelegramBot::setName(const QString &newName) {
    _name = newName;
}

void ITelegramBot::setId(unsigned long long newId) {
    _id = newId;
}

QString ITelegramBot::username() const {
    return _username;
}

QString ITelegramBot::name() const {
    return _name;
}

unsigned long long ITelegramBot::id() const {
    return _id;
}

} // namespace qTbot
