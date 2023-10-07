//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramupdate.h"
#include "qTbot/messages/telegraminlinekeyboardcallback.h"

namespace qTbot {

TelegramUpdate::TelegramUpdate() {
}

bool TelegramUpdate::contains(const Type &type) const  {
    return rawJson().contains(type);
}

QSharedPointer<TelegramMsg> TelegramUpdate::message() const {
    if (!contains(MessageUpdate)) {
        return nullptr;
    }

    return QSharedPointer<TelegramMsg>::create(rawJson()[MessageUpdate].toObject());
}

QSharedPointer<TelegramMsg> TelegramUpdate::editedMessage() const {

    if (!contains(EditedMessageUpdate)) {
        return nullptr;
    }

    return QSharedPointer<TelegramMsg>::create(rawJson()[EditedMessageUpdate].toObject());
}

QJsonObject TelegramUpdate::channelPost() const {
    return rawJson().value(ChannelPostUpdate).toObject();
}

QJsonObject TelegramUpdate::editedChannelPost() const {
    return rawJson().value(EditedChannelPostUpdate).toObject();
}

QJsonObject TelegramUpdate::inlineQueryUpdate() const {
    return rawJson().value(InlineQueryUpdate).toObject();
}

QJsonObject TelegramUpdate::chosenInlineResult() const {
    return rawJson().value(ChosenInlineResultUpdate).toObject();
}

QSharedPointer<TelegramInlineKeyBoardCallBack> TelegramUpdate::callbackQueryUpdate() const {
    if (!contains(CallbackQueryUpdate)) {
        return nullptr;
    }

    return QSharedPointer<TelegramInlineKeyBoardCallBack>::create(rawJson()[CallbackQueryUpdate].toObject());
}

QJsonObject TelegramUpdate::shippingQueryUpdate() const {
    return rawJson().value(ShippingQueryUpdate).toObject();
}

QJsonObject TelegramUpdate::preCheckuptAueryUpdate() const {
    return rawJson().value(PreCheckuptAueryUpdate).toObject();
}

QJsonObject TelegramUpdate::pollUpdate() const {
    return rawJson().value(PollUpdate).toObject();
}

QJsonObject TelegramUpdate::pollAnswerUpdate() const {
    return rawJson().value(PollAnswerUpdate).toObject();
}

QJsonObject TelegramUpdate::myChatMemberUpdate() const {
    return rawJson().value(MyChatMemberUpdate).toObject();
}

QJsonObject TelegramUpdate::chatMemberUpdate() const {
    return rawJson().value(ChatMemberUpdate).toObject();
}

QJsonObject TelegramUpdate::chatJoinRequestUpdate() const {
    return rawJson().value(ChatJoinRequestUpdate).toObject();
}

unsigned long long TelegramUpdate::updateId() const {
    return rawJson().value("update_id").toInteger();
}

bool TelegramUpdate::isValid() const {
    return rawJson().contains("update_id");
}

QString TelegramUpdate::from() const {
    return "";
}

QVariant TelegramUpdate::chatId() const {
    return "";
}

}
