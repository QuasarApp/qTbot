//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramrestbot.h"
#include "qTbot/messages/telegramupdate.h"
#include "qTbot/messages/telegramupdateanswer.h"
#include "requests/telegramgetupdate.h"

#include <QJsonArray>
#include <QTimer>
#include <qTbot/messages/telegrammsg.h>
#include <limits>

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
    _run = true;

    startUpdates();

    return true;
}

void TelegramRestBot::logout() {
    _run = false;
    ITelegramBot::logout();
}

void TelegramRestBot::startUpdates() {
    if (!_run)
        return;

    long long delta = QDateTime::currentMSecsSinceEpoch() - _lanstUpdateTime;


    if (delta >= _updateDelay) {
        auto&& replay = sendRequest(QSharedPointer<TelegramGetUpdate>::create(_lanstUpdateid + 1));

        connect(replay.get(), &QNetworkReply::finished,
                this, std::bind(&TelegramRestBot::handleReceiveUpdates, this, replay.toWeakRef()),
                Qt::DirectConnection);

        connect(replay.get(), &QNetworkReply::errorOccurred,
                this, &TelegramRestBot::handleReceiveUpdatesErr,
                Qt::DirectConnection);

        return;
    } else {
        QTimer::singleShot( _updateDelay - delta, this, [this](){startUpdates();});
    }
}

int TelegramRestBot::updateDelay() const {
    return _updateDelay;
}

void TelegramRestBot::setUpdateDelay(int newUpdateDelay) {
    _updateDelay = newUpdateDelay;
}

void TelegramRestBot::setProcessed(const QSet<unsigned long long> &newProcessed) {
    auto&& it = std::min_element(newProcessed.begin(), newProcessed.end());
    if (it != newProcessed.end()) {
        _lanstUpdateid = *it;
    }

    IBot::setProcessed(newProcessed);
}

void TelegramRestBot::handleReceiveUpdates(const QWeakPointer<QNetworkReply> &replay) {

    if (auto&& sharedReplay = replay.lock()) {
        auto&& telegramMsg = makeMesasge<TelegramUpdateAnswer>(sharedReplay->readAll());
        if (telegramMsg->isValid()) {

            _lanstUpdateTime = QDateTime::currentMSecsSinceEpoch();

            auto && resultArray = telegramMsg->result().toArray();
            for (const auto& ref: resultArray) {
                auto&& update = IBot::makeMesasge<TelegramUpdate>(ref.toObject());
                incomeNewUpdate(update);
                if (_lanstUpdateid < update->updateId()) {
                    _lanstUpdateid = update->updateId();
                };
            }
        }
    }

    startUpdates();
}

void TelegramRestBot::handleReceiveUpdatesErr(QNetworkReply::NetworkError err) {
    if (err) {
        qDebug() << "Network error occured. code: " << err;
    }

    startUpdates();
}


}
