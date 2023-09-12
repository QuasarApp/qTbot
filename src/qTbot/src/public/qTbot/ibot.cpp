//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ibot.h"

namespace qTbot {

IBot::IBot()
{

}

const QByteArray &IBot::token() const {
    return _token;
}

void IBot::setToken(const QByteArray &newToken) {
    _token = newToken;
}

void IBot::incomeNewMessage(const QSharedPointer<iMessage> &message) {
    auto id = message->messageId();

    if (!_processed.contains(id)) {

        _processed.insert(id);
        _notProcessedMessages[message->messageId()] = message;

        emit sigReceiveMessage(message);
    }
}

void IBot::markMessageAsProcessed(const QSharedPointer<iMessage> &message) {
    _notProcessedMessages.remove(message->messageId());
}

const QString &IBot::name() const {
    return _name;
}

void IBot::setName(const QString &newName) {
    _name = newName;
}

QSharedPointer<iMessage> IBot::takeNextUnreadMessage() {
    if (_notProcessedMessages.size()) {
        auto toRemove = std::move(*_notProcessedMessages.begin());
        _notProcessedMessages.erase(_notProcessedMessages.cbegin());
        return toRemove;
    }

    return nullptr;
}


}
