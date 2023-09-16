//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef ITELEGRAMBOT_H
#define ITELEGRAMBOT_H

#include "ibot.h"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

namespace qTbot {

class ITelegramMessage;

/**
 * @brief The ITelegramBot class This is base implementation of the all telegramm bots.
 */
class QTBOT_EXPORT ITelegramBot : public IBot
{
    Q_OBJECT
public:
    ITelegramBot();
    ~ITelegramBot();

    bool login(const QByteArray &token) override;

    bool sendMessage(const QVariant &chatId, const QString& text) override;

    /**
     * @brief Sends a message to a chat or channel.
     *
     * The `sendMessage` method is used to send a message to a chat. This method allows
     * sending text messages to chats and channels. You can also specify additional
     * parameters such as text formatting, a reply to a specific message, and disabling
     * web page preview.
     *
     * @param chatId The identifier of the chat or channel to which the message will be sent.
     *               It can be a string, number, or another valid data type containing the chat identifier.
     * @param text The text of the message to be sent.
     * @param replyToMessageId The identifier of the message to which you want to reply. If you want to send
     *                         a regular message without a reply, leave this field as 0.
     * @param markdown A flag indicating whether the message text should be formatted using Markdown.
     *                If `true`, the text will be formatted using Markdown syntax. If `false`, the text will be
     *                sent as plain text.
     * @param disableWebPagePreview A flag indicating whether to disable web page preview in the message.
     *                             If `true`, web page preview will be disabled.
     * @param cb A callback function to handle the server response after sending the message. This parameter
     *           can be left empty if no callback is required.
     *
     * @return `true` if the message was successfully sent, and `false` otherwise.
     *
     * Usage examples:
     * @code
     * // Send a plain text message
     * bool result = sendMessage(chatId, "Hello, world!");
     *
     * // Send a formatted text message as a reply to another message
     * bool result = sendMessage(chatId, "This is a reply to your message.", messageId);
     *
     * // Send a message with disabled web page preview
     * bool result = sendMessage(chatId, "Check out this website: [OpenAI](https://www.openai.com/)", 0, true, true);
     * @endcode
     */
    bool sendSpecificMessage(const QVariant &chatId,
                             const QString& text,
                             unsigned long long replyToMessageId = 0,
                             bool markdown = true,
                             bool disableWebPagePreview = false,
                             const Responce& cb = {});

//    /*
// **********************************************************************************************************************
// *
// * forwardMessage implementations
// *
// */

//    Message::Id Bot::forwardMessage(const QVariant& chatId, const QVariant& fromChatId, Message::Id messageId);

//    Message::Id Bot::forwardMessage(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * copyMessage implementations
// *
// */

//    Message::Id Bot::copyMessage(const QVariant& chatId, const QVariant& fromChatId, Message::Id messageId);

//    Message::Id Bot::copyMessage(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendPhoto implementations
// *
// */

//    Message::Id Bot::sendPhoto(const QVariant& chatId, QFile *file, const QString& caption, Message::Id replyToMessageId);

//    Message::Id Bot::sendPhoto(const QVariant& chatId, const QString& fileId, const QString& caption, Message::Id replyToMessageId);

//    Message::Id Bot::sendPhoto(const QVariant& chatId, const QByteArray& fileData, const QString& caption, Message::Id replyToMessageId);

//    Message::Id Bot::sendPhoto(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendAudio implementations
// *
// */

//    Message::Id Bot::sendAudio(const QVariant& chatId, QFile *file, qint64 duration, const QString& performer, const QString& title, Message::Id replyToMessageId);

//    Message::Id Bot::sendAudio(const QVariant& chatId, const QString& fileId, qint64 duration, const QString& performer, const QString& title, Message::Id replyToMessageId);

//    Message::Id Bot::sendAudio(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendDocument implementations
// *
// */

//    Message::Id Bot::sendDocument(const QVariant& chatId, QFile *file, Message::Id replyToMessageId);

//    Message::Id Bot::sendDocument(const QVariant& chatId, const QByteArray& fileData, Message::Id replyToMessageId);

//    Message::Id Bot::sendDocument(const QVariant& chatId, const QString& fileId, Message::Id replyToMessageId);

//    Message::Id Bot::sendDocument(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendVideo implementations
// *
// */

//    Message::Id Bot::sendVideo(const QVariant& chatId, QFile *file, qint64 duration, const QString& caption, Message::Id replyToMessageId);

//    Message::Id Bot::sendVideo(const QVariant& chatId, const QString& fileId, qint64 duration, const QString& caption, Message::Id replyToMessageId);

//    Message::Id Bot::sendVideo(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendVoice implementations
// *
// */

//    Message::Id Bot::sendVoice(const QVariant& chatId, QFile *file, qint64 duration, Message::Id replyToMessageId);

//    Message::Id Bot::sendVoice(const QVariant& chatId, const QString& fileId, qint64 duration, Message::Id replyToMessageId);

//    Message::Id Bot::sendVoice(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendLocation implementations
// *
// */

//    Message::Id Bot::sendLocation(const QVariant& chatId, float latitude, float longitude, Message::Id replyToMessageId);

//    Message::Id Bot::sendLocation(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendContact implementations
// *
// */

//    Message::Id Bot::sendContact(const QVariant& chatId, const QString& phoneNumber, const QString& firstName);

//    Message::Id Bot::sendContact(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendPoll implementations
// *
// */

//    Message::Id Bot::sendPoll(const QVariant& chatId, const QString& question, const QStringList& options);

//    Message::Id Bot::sendPoll(const QVariant& chatId, const QString& question, const QStringList& options, bool isAnonymous);

//    Message::Id Bot::sendPoll(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendDice implementations
// *
// */

//    Message::Id Bot::sendDice(const QVariant& chatId, Message::Id replyToMessageId);


//    Message::Id Bot::sendDice(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendChatAction implementations
// *
// */

//    bool Bot::sendChatAction(const QVariant& chatId, Bot::ChatAction action);

//    bool Bot::sendChatAction(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * getUserProfilePhotos implementations
// *
// */

//    UserProfilePhotos Bot::getUserProfilePhotos(User::Id userId, qint16 offset, qint8 limit);

//    UserProfilePhotos Bot::getUserProfilePhotos(ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * getFile implementations
// *
// */

//    File Bot::getFile(const QString& fileId);

//    File Bot::getFile(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * banChatMember implementations
// *
// */

//    bool Bot::banChatMember(const QVariant& chatId, User::Id userId);

//    bool Bot::banChatMember(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * unbanChatMember implementations
// *
// */

//    bool Bot::unbanChatMember(const QVariant& chatId, User::Id userId);

//    bool Bot::unbanChatMember(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * restrictChatMember implementations
// *
// */

//    bool Bot::restrictChatMember(const QVariant& chatId, const QVariant& userId, qint32 untilDate, bool canSendMessages, bool can_send_media_messages,bool can_send_other_messages,bool can_add_web_page_previews);

//    bool Bot::restrictChatMember(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * setChatAdministratorCustomTitle implementations
// *
// */

//    bool Bot::setChatAdministratorCustomTitle(const QVariant& chatId, User::Id userId,const QString& customTitle);

//    bool Bot::setChatAdministratorCustomTitle(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * banChatSenderChat implementations
// *
// */

//    bool Bot::banChatSenderChat(const QVariant& chatId,const QVariant& senderChatId);

//    bool Bot::banChatSenderChat(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * unbanChatSenderChat implementations
// *
// */

//    bool Bot::unbanChatSenderChat(const QVariant& chatId,const QVariant& senderChatId);

//    bool Bot::unbanChatSenderChat(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * exportChatInviteLink implementations
// *
// */

//    QString Bot::exportChatInviteLink(const QVariant& chatId);

//    QString Bot::exportChatInviteLink(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * approveChatJoinRequest implementations
// *
// */

//    bool Bot::approveChatJoinRequest(const QVariant& chatId, User::Id userId);

//    bool Bot::approveChatJoinRequest(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * declineChatJoinRequest implementations
// *
// */

//    bool Bot::declineChatJoinRequest(const QVariant& chatId, User::Id userId);

//    bool Bot::declineChatJoinRequest(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * setChatTitle implementations
// *
// */

//    bool Bot::setChatTitle(const QVariant& chatId, const QString& title);

//    bool Bot::setChatTitle(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * pinChatMessage implementations
// *
// */

//    bool Bot::pinChatMessage(const QVariant& chatId,Message::Id messageId);

//    bool Bot::pinChatMessage(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * unpinChatMessage implementations
// *
// */

//    bool Bot::unpinChatMessage(const QVariant& chatId,Message::Id messageId);

//    bool Bot::unpinChatMessage(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * unpinAllChatMessages implementations
// *
// */

//    bool Bot::unpinAllChatMessages(const QVariant& chatId);

//    bool Bot::unpinAllChatMessages(const ParameterList& params);


//    /*
// **********************************************************************************************************************
// *
// * leaveChat implementations
// *
// */

//    bool Bot::leaveChat(const QVariant& chatId);

//    bool Bot::leaveChat(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * getChat implementations
// *
// */

//    Chat Bot::getChat(const QVariant& chatId);

//    Chat Bot::getChat(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * getChatAdministrators implementations
// *
// */

//    QList<ChatMember> Bot::getChatAdministrators(const QVariant& chatId);

//    QList<ChatMember> Bot::getChatAdministrators(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * getChatMemberCount implementations
// *
// */

//    int Bot::getChatMemberCount(const QVariant& chatId);

//    int Bot::getChatMemberCount(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * getChatMember implementations
// *
// */

//    ChatMember Bot::getChatMember(const QVariant& chatId,User::Id userId);

//    ChatMember Bot::getChatMember(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * answerCallbackQuery implementations
// *
// */

//    bool Bot::answerCallbackQuery(const QString& callbackQueryId,const QString& text,bool showAlert, const QString& url,qint32 cahceTime);

//    bool Bot::answerCallbackQuery(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * getMyCommands implementations
// *
// */

//    bool Bot::setMyCommands(const BotCommandList& commands);

//    bool Bot::setMyCommands(const BotCommandList& commands,const GenericScope& commandScope);

//    bool Bot::setMyCommands(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * deleteMyCommands implementations
// *
// */

//    bool Bot::deleteMyCommands();

//    bool Bot::deleteMyCommands(const GenericScope& commandScope);

//    bool Bot::deleteMyCommands(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * getMyCommands implementations
// *
// */

//    BotCommandList Bot::getMyCommands();

//    BotCommandList Bot::getMyCommands(const GenericScope& commandScope);

//    BotCommandList Bot::getMyCommands(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * editMessageText implementations
// *
// */

//    bool Bot::editMessageText(const QVariant& chatId,Message::Id messageId,const QString& text);

//    bool Bot::editMessageText(const QVariant& chatId,Message::Id messageId,const QString& text, const GenericReply &replyMarkup);

//    bool Bot::editMessageText(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * editMessageReplyMarkup implementations
// *
// */

//    bool Bot::editMessageReplyMarkup(const QVariant& chatId, Message::Id messageId, const GenericReply& replyMarkup);

//    bool Bot::editMessageReplyMarkup(const QString& inlineMessageId, const GenericReply& replyMarkup);

//    bool Bot::editMessageReplyMarkup(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * stopPoll implementations
// *
// */

//    bool Bot::stopPoll(const QVariant& chatId, Message::Id messageId);

//    bool Bot::stopPoll(const QVariant& chatId,int messageId,const GenericReply& replyMarkup);

//    bool Bot::stopPoll(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * deleteMessage implementations
// *
// */

//    bool Bot::deleteMessage(const QVariant& chatId,Message::Id messageId);

//    bool Bot::deleteMessage(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * sendSticker implementations
// *
// */

//    Message::Id Bot::sendSticker(const QVariant& chatId, const QString& sticker);

//    Message::Id Bot::sendSticker(const ParameterList& params);

//    /*
// **********************************************************************************************************************
// *
// * Internal methods
// *
// */

//    QJsonObject Bot::sendFilePayload(ParameterList params, QFile *filePayload, const QString& payloadType, const QString& endpoint);

//    QJsonObject Bot::sendFilePayload(ParameterList params, const QByteArray& fileData, const QString& payloadType, const QString& endpoint);


    /**
     * @brief id This method return bots id number.
      * @return bots id number.
     */
    unsigned long long id() const;

    /**
     * @brief username This is bots login
     * @return bots login.
     */
    const QString& username() const;

protected:
    /**
     * @brief setId This method sets new value for the ITelegramBot::id property.
     * @param newId this is new value of the ITelegramBot::id property.
     */
    void setId(unsigned long long newId);

    /**
     * @brief setUsername This method sets new value for the ITelegramBot::username property.
     * @param newUsername this is new value of the ITelegramBot::username property.
     */
    void setUsername(const QString &newUsername);

    /**
     * @brief makePrefix This method prepare a prefix message for all telegramm bots.
     * @return telegramm request prefix/
     */
    QByteArray makePrefix() const;

    bool sendRequest(const QSharedPointer<iRequest>& rquest, const Responce& cb) override;

private:
    unsigned long long _id = 0;
    QString _username;

    QNetworkAccessManager *_manager = nullptr;

};
}
#endif // ITELEGRAMBOT_H
