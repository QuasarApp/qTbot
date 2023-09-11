//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramrestbot.h"
#include "qTbot/messages/telegramupdateansver.h"
#include "qTbot/requests/telegramgetupdate.h"

#include <QJsonArray>
#include <QTimer>
#include <qTbot/messages/telegrammsg.h>

namespace qTbot {

TelegramRestBot::TelegramRestBot() {
}

TelegramRestBot::~TelegramRestBot() {
}

bool TelegramRestBot::login(const QByteArray &token) {
    if (!ITelegramBot::login(token)) {
        return false;
    }

    _lanstUpdateTime = QDateTime::currentMSecsSinceEpoch();

    startUpdates();

    return true;
}

void TelegramRestBot::startUpdates() {
    long long delta = QDateTime::currentMSecsSinceEpoch() - _lanstUpdateTime;

    TelegramRestBot::Responce cb = [this] (auto, const QSharedPointer<iMessage>& responce, int err) {
        _lanstUpdateTime = QDateTime::currentMSecsSinceEpoch();

        if (err) {
            qDebug() << "Network error occured. code: " << err;
        }

        if (auto telegramMsg = responce.dynamicCast<TelegramUpdateAnsver>()) {
            if (telegramMsg->isValid()) {
                auto && resultArray = telegramMsg->result().toArray();
                for (const auto& ref: resultArray) {
                    auto message = QSharedPointer<TelegramMsg>::create();
                    message->setRawJson(ref.toObject());
                    emit sigReceiveMessage(telegramMsg);
                }
            }
        };

        startUpdates();

    };

    if (delta >= _updateDelay) {
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
