//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "itelegrammessage.h"
#include <QJsonDocument>

namespace qTbot {

ITelegramMessage::ITelegramMessage():iMessage(){}

QByteArray ITelegramMessage::makeUpload() const {
    return QJsonDocument(_rawJson).toJson(QJsonDocument::Compact);
}

const QJsonObject &ITelegramMessage::rawJson() const {
    return _rawJson;
}

void ITelegramMessage::setRawJson(const QJsonObject &newRawJson) {
    _rawJson = newRawJson;
}

void ITelegramMessage::setRawData(const QByteArray &newRawData) {
    iMessage::setRawData(newRawData);

    auto doc = QJsonDocument::fromJson(newRawData);
    if (!doc.isObject()) {
        return;
    }
    setRawJson(doc.object());

}

QJsonValue ITelegramMessage::result() const {
    return _rawJson.value("result");
}

int ITelegramMessage::messageId() const {
    return rawJsonObject()["message_id"].toInt();
}

int ITelegramMessage::fromId() const {
    return rawJsonObject()["from"]["id"].toInt();
}

bool ITelegramMessage::isBot() const {
    return rawJsonObject()["from"]["is_bot"].toBool();
}

QString ITelegramMessage::firstName() const {
    return rawJsonObject()["from"]["first_name"].toString();
}

QString ITelegramMessage::lastName() const {
    return rawJsonObject()["from"]["last_name"].toString();
}

QString ITelegramMessage::username() const {
    return rawJsonObject()["from"]["username"].toString();
}

QString ITelegramMessage::languageCode() const {
    return rawJsonObject()["from"]["language_code"].toString();
}

int ITelegramMessage::chatId() const {
    return rawJsonObject()["chat"]["id"].toInt();
}

QString ITelegramMessage::chatFirstName() const {
    return rawJsonObject()["chat"]["first_name"].toString();
}

QString ITelegramMessage::chatLastName() const {
    return rawJsonObject()["chat"]["last_name"].toString();
}

QString ITelegramMessage::chatUsername() const {
    return rawJsonObject()["chat"]["username"].toString();
}

QString ITelegramMessage::chatType() const {
    return rawJsonObject()["chat"]["type"].toString();
}

const QJsonObject &ITelegramMessage::rawJsonObject() const {
    return _rawJson;
}

bool ITelegramMessage::isValid() const {
    return _rawJson.value("ok").toBool();
}

}
