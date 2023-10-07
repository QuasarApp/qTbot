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
class TelegramFile;
class TelegramUpdateAnswer;

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
     * @brief Sends a message to a chat or channel with optional additional objects.
     *
     * The `sendSpecificMessage` method is used to send a message to a chat. This method allows
     * sending text messages to chats and channels. You can also specify additional
     * parameters such as text formatting, a reply to a specific message, disabling
     * web page preview, and including extra JSON objects in the message.
     *
     * @param chatId The identifier of the chat or channel to which the message will be sent.
     *               It can be a string, number, or another valid data type containing the chat identifier.
     * @param text The text of the message to be sent.
     * @param extraObjects A map containing additional JSON objects to include in the message.
     * @param replyToMessageId The identifier of the message to which you want to reply. If you want to send
     *                         a regular message without a reply, leave this field as 0.
     * @param markdown A flag indicating whether the message text should be formatted using Markdown.
     *                If `true`, the text will be formatted using Markdown syntax. If `false`, the text will be
     *                sent as plain text.
     * @param disableWebPagePreview A flag indicating whether to disable web page preview in the message.
     *                             If `true`, web page preview will be disabled.
     *
     * @return `true` if the message was successfully sent, and `false` otherwise.
     *
     * Usage examples:
     * @code
     * // Send a plain text message
     * bool result = sendSpecificMessage(chatId, "Hello, world!");
     *
     * // Send a formatted text message as a reply to another message with additional JSON objects
     * QMap<QString, QJsonObject> additionalObjects = {
     *     {"key1", {"value1"}},
     *     {"key2", {"value2"}}
     * };
     * bool result = sendSpecificMessage(chatId, "This is a reply with additional objects.", additionalObjects, messageId);
     *
     * // Send a message with disabled web page preview
     * bool result = sendSpecificMessage(chatId, "Check)", {}, 0, true, true);
     * @endcode
     */
    bool sendSpecificMessage(const QVariant &chatId,
                             const QString& text,
                             const QMap<QString, QJsonObject> &extraObjects = {},
                             const QString &callBackQueryId = {},
                             unsigned long long replyToMessageId = 0,
                             bool markdown = true,
                             bool disableWebPagePreview = false);

    /**
     * @brief Sends a message to a chat or channel with an optional custom **inline keyboard**.
     *
     * The `sendSpecificMessage` method is used to send a message to a chat or channel. This method allows
     * sending text messages with optional interactive **inline keyboards** to chats and channels. You can also specify
     * additional parameters such as text formatting, replying to a specific message, disabling web page preview,
     * and providing a custom inline keyboard for user interaction.
     *
     * @param chatId The identifier of the chat or channel to which the message will be sent. It can be a string,
     *               number, or another valid data type containing the chat identifier.
     * @param text The text of the message to be sent.
     * @param keyboard A list of maps, each containing buttons and corresponding callback functions for a custom inline keyboard.
     *                Each map should have button text as the key and a callback function as the value.
     * @param onTimeKeyboard A flag indicating whether the inline keyboard should be hidden after the user interacts with it
     *                       (one-time keyboard). Default is `false`.
     * @param autoResizeKeyboard A flag indicating whether the inline keyboard should automatically adjust its size based on
     *                           the number of buttons. Default is `false`.
     * @param replyToMessageId The identifier of the message to which you want to reply. If you want to send a regular message
     *                         without replying to another message, leave this field as 0. Default is 0.
     * @param markdown A flag indicating whether the message text should be formatted using Markdown syntax. If `true`, the text
     *                will be formatted using Markdown. If `false`, the text will be sent as plain text. Default is `true`.
     * @param disableWebPagePreview A flag indicating whether to disable web page preview in the message. If `true`, web page
     *                             preview will be disabled. Default is `false`.
     *
     * @return `true` if the message was successfully sent, and `false` otherwise.
     *
     * Usage examples:
     * @code
     * // Send a plain text message
     * bool result = sendSpecificMessage(chatId, "Hello, world!");
     *
     * // Send a formatted text message as a reply to another message with a custom inline keyboard
     * QList<QMap<QString, std::function<void()>>> customKeyboard = {
     *     {
     *         {"Button 1", []() {  Callback function for Button 1  }},
     *         {"Button 2", []() {  Callback function for Button 2  }}
     *     }
     * };
     * bool result = sendSpecificMessage(chatId, "This is a reply with a custom inline keyboard.", customKeyboard, true, false, messageId);
     *
     * // Send a message with disabled web page preview
     * bool result = sendSpecificMessage(chatId, "Check)", {}, false, true, 0, false, true);
     * @endcode
     */
    bool sendSpecificMessageWithKeyboard(const QVariant &chatId,
                             const QString& text,
                             const QList<QMap<QString, std::function<void (const QString &queryID)> > > &keyboard,
                             const QString &callBackQueryId,
                             bool onTimeKeyboard = false,
                             bool autoResizeKeyboard = false,
                             unsigned long long replyToMessageId = 0,
                             bool markdown = true,
                             bool disableWebPagePreview = false);

    /**
     * @brief sendSpecificMessageWithKeyBoard sends a specific message with a keyboard to a chat.
     *
     * This method sends a specific message with a keyboard to a chat. It allows
     * you to customize various aspects of the message, such as the text, keyboard,
     * and other options.
     *
     * @param chatId The identifier of the chat to which the message will be sent.
     * @param text The text of the message to be sent.
     * @param keyboard A list of text buttons for the keyboard placed below the message.
     * @param onTimeKeyboard A flag indicating whether the keyboard should be hidden after
     * selecting one of the buttons (one-time keyboard).
     * @param autoResizeKeyboard A flag indicating whether the keyboard should automatically
     * adjust its size based on the number of buttons.
     * @param replyToMessageId The identifier of the message to which this message is a reply
     * (if applicable).
     * @param markdown A flag indicating whether Markdown formatting is supported in the message text.
     * @param disableWebPagePreview A flag indicating whether to disable web page preview in the message.
     *
     * @return Returns true if the message was successfully sent, and false in case of an error.
     *
     * @example
     * @code
     * bool result = sendSpecificMessage(chatId, "Hello, how are you?", {"Button 1", "Button 2"}, true, true, 0, true, false);
     * if (result) {
     *     qDebug() << "Message sent successfully.";
     * } else {
     *     qDebug() << "Error sending the message.";
     * }
     * @endcode
     *
     * @note If the onTimeKeyboard parameter is set to true, the keyboard will be hidden after selecting
     * one of the buttons, and the user won't be able to use it again.
     * @note If the autoResizeKeyboard parameter is set to true, the keyboard will automatically adjust
     * its size based on the number of buttons.
     * @note The markdown and disableWebPagePreview parameters allow you to configure text formatting
     * and web page preview options in the message.
     */
    bool sendSpecificMessageWithKeyboard(const QVariant &chatId,
                             const QString& text,
                             const QList<QString> &keyboard,
                             const QString &callBackQueryId,
                             bool onTimeKeyboard = false,
                             bool autoResizeKeyboard = false,
                             unsigned long long replyToMessageId = 0,
                             bool markdown = true,
                             bool disableWebPagePreview = false);

    [[nodiscard("do not forget to save shared pointer of file handler, because it's will not save inner bot object.")]]
    QSharedPointer<iFile> getFile(const QString& fileId, iFile::Type fileType = iFile::Type::Ram) override;

    /**
     * @brief getFileMeta This method receive meta information of the file.
     * @param fileId This is id of the file.
     * @param receiver this is wrapper of the file. Set to nullptr if you no need to wait a physical file.
     * @return true if the reqests sents successful.
     */
    QSharedPointer<QNetworkReply> getFileMeta(const QString& fileId,
                                              const QWeakPointer<iFile> &receiver = {nullptr});
// to do

// * forwardMessage implementations
// * copyMessage implementations
// * sendPhoto implementations
// * sendAudio implementations
// * sendDocument implementations
// * sendVideo implementations
// * sendVoice implementations
// * sendLocation implementations
// * sendContact implementations
// * sendPoll implementations
// * sendDice implementations
// * sendChatAction implementations
// * getUserProfilePhotos implementations
// * banChatMember implementations
// * unbanChatMember implementations
// * restrictChatMember implementations
// * setChatAdministratorCustomTitle implementations
// * banChatSenderChat implementations
// * unbanChatSenderChat implementations
// * exportChatInviteLink implementations
// * approveChatJoinRequest implementations
// * declineChatJoinRequest implementations
// * setChatTitle implementations
// * pinChatMessage implementations
// * unpinChatMessage implementations
// * unpinAllChatMessages implementations
// * leaveChat implementations
// * getChat implementations
// * getChatAdministrators implementations
// * getChatMemberCount implementations
// * getChatMember implementations
// * answerCallbackQuery implementations
// * getMyCommands implementations
// * deleteMyCommands implementations
// * getMyCommands implementations
// * editMessageText implementations
// * editMessageReplyMarkup implementations
// * stopPoll implementations
// * deleteMessage implementations
// * sendSticker implementations


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

    QString makeUrl(const QSharedPointer<iRequest>& request) const override;

    /**
     * @brief getFileSizeByUniqueId This method return size of the file by id
     * @param id This is id of required file.
     * @return file size - else 0
     */
    int getFileSizeByUniqueId(const QString& id) const;

    /**
     * @brief getFileInfoByUniqueId return a local saved meta information about the file.
     * @param id This is id of the file.
     * @return shared pointer to the meta information of the file. If information no exists return nullptr;
     */
    QSharedPointer<TelegramFile> getFileInfoByUniqueId(const QString& id) const;

    /**
     * @brief onRequestError This method invokent when telegram server sent error responce. Default implementation just print error message on the console.
     * @param ansverWithError - This is ansver object with error descriptions. and codes errors.
     */
    virtual void onRequestError(const QSharedPointer<TelegramUpdateAnswer>& ansverWithError) const;

    void handleIncomeNewUpdate(const QSharedPointer<iUpdate> &) override;

private slots:
    void handleLogin();
    void handleLoginErr(QNetworkReply::NetworkError err);
    void handleFileHeader(const QWeakPointer<QNetworkReply>& sender,
                          const QWeakPointer<iFile> &receiver);

private:
    QString findFileInlocatStorage(const QString& fileId) const;

    unsigned long long _id = 0;
    QString _username;
    QSharedPointer<QNetworkReply> _loginReplay;
    QMap<QString, QPair<std::function<void(const QString&)>, bool>> _handleButtons;

    QHash<QString, QSharedPointer<TelegramFile>> _filesMetaInfo;

};
}
#endif // ITELEGRAMBOT_H
