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
    _timer = new QTimer();
    _timer->start(2000);

    connect(_timer, &QTimer::timeout, this, &TelegramRestBot::handleTimeOut,
            Qt::QueuedConnection);
}

TelegramRestBot::~TelegramRestBot() {
    delete _timer;
}

bool TelegramRestBot::login(const QByteArray &token) {
    if (!ITelegramBot::login(token)) {
        return false;
    }

    _timer->start();

    return true;
}

int TelegramRestBot::interval() const {
    return _timer->interval();
}

void TelegramRestBot::setInterval(int newInterval) {
    _timer->setInterval(newInterval);
}

void TelegramRestBot::handleTimeOut() {
    sendMessage(QSharedPointer<TelegramGetUpdate>::create());
}

}
