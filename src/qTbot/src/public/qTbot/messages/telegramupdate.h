//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMUPDATE_H
#define TELEGRAMUPDATE_H


#include <qTbot/ijsonbasedupdate.h>
#include "telegraminlinekeyboardcallback.h"
#include "telegrammsg.h"

namespace qTbot {

/**
 * @brief The TelegramUpdate class contains base information about updates from telegram.
 */
class QTBOT_EXPORT TelegramUpdate: public IJsonBasedUpdate
{
public:
    /**
     * @brief TelegramUpdate default constructor.
     */
    TelegramUpdate();

    /**
     * @brief Type This is a string value of the telegram update types.
     */
    using Type = QString;

    /**
     * @brief MessageUpdate This is the type of a normal message update.
     */
    const Type MessageUpdate = "message";
    /**
     * @brief EditedMessageUpdate This is the type of an edited message update.
     */
    const Type EditedMessageUpdate = "edited_message";
    /**
     * @brief ChannelPostUpdate This is the type of a channel post update.
     */
    const Type ChannelPostUpdate = "channel_post";
    /**
     * @brief EditedChannelPostUpdate This is the type of an edited channel post update.
     */
    const Type EditedChannelPostUpdate = "edited_channel_post";
    /**
     * @brief InlineQueryUpdate This is the type of an inline query update.
     */
    const Type InlineQueryUpdate = "inline_query";
    /**
     * @brief ChosenInlineResultUpdate This is the type of a chosen inline result update.
     */
    const Type ChosenInlineResultUpdate = "chosen_inline_result";
    /**
     * @brief CallbackQueryUpdate This is the type of a callback query update.
     */
    const Type CallbackQueryUpdate = "callback_query";
    /**
     * @brief ShippingQueryUpdate This is the type of a shipping query update.
     */
    const Type ShippingQueryUpdate = "shipping_query";
    /**
     * @brief PreCheckuptAueryUpdate This is the type of a pre-checkout query update.
     */
    const Type PreCheckuptAueryUpdate = "pre_checkout_query";
    /**
     * @brief PollUpdate This is the type of a poll update.
     */
    const Type PollUpdate = "poll";
    /**
     * @brief PollAnswerUpdate This is the type of a poll answer update.
     */
    const Type PollAnswerUpdate = "poll_answer";
    /**
     * @brief MyChatMemberUpdate This is the type of a my chat member update.
     */
    const Type MyChatMemberUpdate = "my_chat_member";
    /**
     * @brief ChatMemberUpdate This is the type of a chat member update.
     */
    const Type ChatMemberUpdate = "chat_member";
    /**
     * @brief ChatJoinRequestUpdate This is the type of a chat join request update.
     */
    const Type ChatJoinRequestUpdate = "chat_join_request";

    /**
     * @brief contains This method returns true if the update contains the chosen data type.
     * @param type This is the name of the type
     * @return true if the chosen type is available in this update.
     */
    bool contains(const Type& type) const;

    /**
     * @brief message Returns the message of this update.
     * @return the message of the update.
     */
    QSharedPointer<TelegramMsg> message() const;

    /**
     * @brief editedMessage Returns the edited message of this update.
     * @return The edited message of the update.
     */
    QSharedPointer<TelegramMsg> editedMessage() const;

    /**
     * @brief channelPost Returns the channel post of this update.
     * @return The channel post of the update.
     */
    QJsonObject channelPost() const;

    /**
     * @brief editedChannelPost Returns the edited channel post of this update.
     * @return The edited channel post of the update.
     */
    QJsonObject editedChannelPost() const;

    /**
     * @brief inlineQueryUpdate Returns the inline query of this update.
     * @return The inline query of the update.
     */
    QJsonObject inlineQueryUpdate() const;

    /**
     * @brief chosenInlineResult Returns the chosen inline result of this update.
     * @return The chosen inline result of the update.
     */
    QJsonObject chosenInlineResult() const;

    /**
     * @brief callbackQueryUpdate Returns the callback query of this update.
     * @return The callback query of the update.
     */
    QSharedPointer<TelegramInlineKeyBoardCallBack> callbackQueryUpdate() const;

    /**
     * @brief shippingQueryUpdate Returns the shipping query of this update.
     * @return The shipping query of the update.
     */
    QJsonObject shippingQueryUpdate() const;

    /**
     * @brief preCheckuptAueryUpdate Returns the pre-checkout query of this update.
     * @return The pre-checkout query of the update.
     */
    QJsonObject preCheckuptAueryUpdate() const;

    /**
     * @brief pollUpdate Returns the poll of this update.
     * @return The poll of the update.
     */
    QJsonObject pollUpdate() const;

    /**
     * @brief pollAnswerUpdate Returns the poll answer of this update.
     * @return The poll answer of the update.
     */
    QJsonObject pollAnswerUpdate() const;

    /**
     * @brief myChatMemberUpdate Returns the my chat member of this update.
     * @return The my chat member of the update.
     */
    QJsonObject myChatMemberUpdate() const;

    /**
     * @brief chatMemberUpdate Returns the chat member of this update.
     * @return The chat member of the update.
     */
    QJsonObject chatMemberUpdate() const;

    /**
     * @brief chatJoinRequestUpdate Returns the chat join request of this update.
     * @return The chat join request of the update.
     */
    QJsonObject chatJoinRequestUpdate() const;

    /**
     * @brief updateId Returns the update ID.
     * @return The update ID.
     */
    unsigned long long updateId() const override;
    // iMessage interface
public:
    bool isValid() const override;
    QString from() const override;
    QVariant chatId() const override;
};
}
#endif // TELEGRAMUPDATE_H
