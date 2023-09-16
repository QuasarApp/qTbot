//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegrammsg.h"
#include "qjsonarray.h"
namespace qTbot {


TelegramMsg::TelegramMsg()
{

}

unsigned long long TelegramMsg::messageId() const {
    return rawJson()["message_id"].toInteger();
}

unsigned long long TelegramMsg::fromId() const {
    return rawJson()["from"]["id"].toInteger();
}

bool TelegramMsg::isBot() const {
    return rawJson()["from"]["is_bot"].toBool();
}

QString TelegramMsg::firstName() const {
    return rawJson()["from"]["first_name"].toString();
}

QString TelegramMsg::lastName() const {
    return rawJson()["from"]["last_name"].toString();
}

QString TelegramMsg::username() const {
    return rawJson()["from"]["username"].toString();
}

QString TelegramMsg::languageCode() const {
    return rawJson()["from"]["language_code"].toString();
}

int TelegramMsg::chatId() const {
    return rawJson()["chat"]["id"].toInt();
}

QString TelegramMsg::from() const {
    return chatUsername();
}

QString TelegramMsg::chatFirstName() const {
    return rawJson()["chat"]["first_name"].toString();
}

QString TelegramMsg::chatLastName() const {
    return rawJson()["chat"]["last_name"].toString();
}

QString TelegramMsg::chatUsername() const {
    return rawJson()["chat"]["username"].toString();
}

QString TelegramMsg::chatType() const {
    return rawJson()["chat"]["type"].toString();
}

qint64 TelegramMsg::date() const {
    return rawJson()["date"].toVariant().toLongLong();
}

QString TelegramMsg::text() const {
    return rawJson()["text"].toString();
}

bool TelegramMsg::contains(const Type &type) {
    return rawJson().contains(type);
}

QList<TelegramImage> TelegramMsg::images() const {
    const QJsonArray&& array = rawJson()["photo"].toArray();
    QList<TelegramImage> result;

    for (const auto& photo: array) {
        result.push_back({photo.toObject()});
    }

    return result;
}

TelegramImage TelegramMsg::image(QualitySelector behavior, int size) const {
    const QJsonArray&& array = rawJson()["photo"].toArray();
    TelegramImage result;

    switch (behavior) {
    case QualitySelector::AroundSize:
    {
        int oldBestMath = std::numeric_limits<decltype(oldBestMath)>::max();
        auto it = array.cbegin();

        result.setRawJson(it->toObject());
        it = std::next(it);

        while (it != array.end() || std::abs(result.fileSize() - size) < oldBestMath) {
            oldBestMath = std::abs(result.fileSize() - size);
            result.setRawJson(it->toObject());
            it = std::next(it);
        }

        return result;
    }
    case QualitySelector::BestOf: {
        for (const auto& photo: array) {
            auto photoObj = TelegramImage{photo.toObject()};
            if (photoObj.fileSize() < size) {
                result.setRawJson(photoObj.rawJson());
            } else {
                return result;
            }
        }

        return result;
    }
    case QualitySelector::Best: {
        if (array.size()) {
            return std::prev(array.end())->toObject();
        }

        return result;
    }

    case QualitySelector::Fast: {
        if (array.size()) {
            return array.begin()->toObject();
        }

        return result;
    }

    break;
    default:
        break;
    }

    return result;
}

TelegramDocument TelegramMsg::documents() const {
    return rawJson()[Document].toObject();
}

TelegramAudio TelegramMsg::audio() const {
    return rawJson()[Audio].toObject();
}

}
