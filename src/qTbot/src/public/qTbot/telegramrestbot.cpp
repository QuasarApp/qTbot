//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramrestbot.h"

#include <qTbot/messages/telegramgetupdate.h>

#include <QTimer>

namespace qTbot {

TelegramRestBot::TelegramRestBot() {
}

TelegramRestBot::~TelegramRestBot() {
}

bool TelegramRestBot::login(const QByteArray &token) {
    if (!ITelegramBot::login(token)) {
        return false;
    }

    TelegramRestBot::Responce cb = [] (auto request, auto responce) {

    };

    return sendRequest(QSharedPointer<TelegramGetUpdate>::create(), cb);
}

void TelegramRestBot::startUpdates() {
    long long delta = QDateTime::currentMSecsSinceEpoch() - _lanstUpdateTime;

    TelegramRestBot::Responce cb = [this] (auto request, auto responce) {

        startUpdates();
    };

    if (delta > _updateDelay) {
        sendRequest(QSharedPointer<TelegramGetUpdate>::create(), cb);
        return;
    }

    QTimer::singleShot( _updateDelay - delta, this, [this](){startUpdates();});
}

int TelegramRestBot::updateDelay() const {
    return _updateDelay;
}

void TelegramRestBot::setUpdateDelay(int newUpdateDelay) {
    _updateDelay = newUpdateDelay;
}


}
