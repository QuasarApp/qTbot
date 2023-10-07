//#
//# Copyright (C) 2023-2023 QuasarApp.
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
 * @brief The TelegramUpdate class contains base information about updates from telegram
 */
class QTBOT_EXPORT TelegramUpdate: public IJsonBasedUpdate
{
public:
    TelegramUpdate();

    /**
     * @brief Type just string value of the telegram messages types.
     */
    using Type = QString;

    const Type MessageUpdate = "message";
    const Type EditedMessageUpdate = "edited_message";
    const Type ChannelPostUpdate = "channel_post";
    const Type EditedChannelPostUpdate = "edited_channel_post";
    const Type InlineQueryUpdate = "inline_query";
    const Type ChosenInlineResultUpdate = "chosen_inline_result";
    const Type CallbackQueryUpdate = "callback_query";
    const Type ShippingQueryUpdate = "shipping_query";
    const Type PreCheckuptAueryUpdate = "pre_checkout_query";
    const Type PollUpdate = "poll";
    const Type PollAnswerUpdate = "poll_answer";
    const Type MyChatMemberUpdate = "my_chat_member";
    const Type ChatMemberUpdate = "chat_member";
    const Type ChatJoinRequestUpdate = "chat_join_request";

    /**
     * @brief contains This method returns true if the message contains choosed data type.
     * @param type This is name of the type
     * @return true if the choosed type is available in this message.
     */
    bool contains(const Type& type) const;

    /**
     * @brief message returns the array of the updates messages.
     * @return list of updates.
     */
    QSharedPointer<TelegramMsg> message() const;

    /**
     * @brief editedMessage returns the edited message update.
     * @return QJsonObject containing the edited message update.
     */
    QSharedPointer<TelegramMsg> editedMessage() const;

    /**
     * @brief channelPost returns the channel post update.
     * @return QJsonObject containing the channel post update.
     */
    QJsonObject channelPost() const;

    /**
     * @brief editedChannelPost returns the edited channel post update.
     * @return QJsonObject containing the edited channel post update.
     */
    QJsonObject editedChannelPost() const;

    /**
     * @brief inlineQueryUpdate returns the inline query update.
     * @return QJsonObject containing the inline query update.
     */
    QJsonObject inlineQueryUpdate() const;

    /**
     * @brief chosenInlineResult returns the chosen inline result update.
     * @return QJsonObject containing the chosen inline result update.
     */
    QJsonObject chosenInlineResult() const;

    /**
     * @brief callbackQueryUpdate returns the callback query update.
     * @return QJsonObject containing the callback query update.
     */
    QSharedPointer<TelegramInlineKeyBoardCallBack> callbackQueryUpdate() const;

    /**
     * @brief shippingQueryUpdate returns the shipping query update.
     * @return QJsonObject containing the shipping query update.
     */
    QJsonObject shippingQueryUpdate() const;

    /**
     * @brief preCheckuptAueryUpdate returns the pre-checkout query update.
     * @return QJsonObject containing the pre-checkout query update.
     */
    QJsonObject preCheckuptAueryUpdate() const;

    /**
     * @brief pollUpdate returns the poll update.
     * @return QJsonObject containing the poll update.
     */
    QJsonObject pollUpdate() const;

    /**
     * @brief pollAnswerUpdate returns the poll answer update.
     * @return QJsonObject containing the poll answer update.
     */
    QJsonObject pollAnswerUpdate() const;

    /**
     * @brief myChatMemberUpdate returns the my chat member update.
     * @return QJsonObject containing the my chat member update.
     */
    QJsonObject myChatMemberUpdate() const;

    /**
     * @brief chatMemberUpdate returns the chat member update.
     * @return QJsonObject containing the chat member update.
     */
    QJsonObject chatMemberUpdate() const;

    /**
     * @brief chatJoinRequestUpdate returns the chat join request update.
     * @return QJsonObject containing the chat join request update.
     */
    QJsonObject chatJoinRequestUpdate() const;

    /**
     * @brief updateId returns the update ID.
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
