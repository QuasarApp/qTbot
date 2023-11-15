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
class TelegramSendFile;
class TelegramSingleRquest;

typedef std::function<void(const QString& buttonKey, const QVariant& msgID)> ButtonCB;
typedef QList<QHash<QString, ButtonCB >> KeyboardOnMessage;

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
     * @brief Sends a specific message to a chat.
     *
     * This function sends a specific message to a chat. You can include text and additional objects as needed to customize the message's content and behavior.
     *
     * @param chatId The unique identifier of the chat to send the message to.
     * @param text The text content of the message to be sent.
     * @param extraObjects A map containing additional objects associated with the message (optional).
     * @param callBackQueryId The unique identifier for callback queries triggered by the message (optional).
     * @param replyToMessageId The unique identifier of the message to reply to, if any (optional).
     * @param parseMode Sets a text parsing mode. supports markdown and html, by default will be used html mode. If you want to disable parsing mode sets this option to empty string.
     * @param disableWebPagePreview Set to true to disable web page previews for links in the message (optional).
     *
     * @return Returns true if the message was sent successfully, false otherwise.
     *
     * @note The extraObjects parameter is a map where each key represents the object's name, and the associated value is a shared pointer to a JSON object (optional).
     * @note The callBackQueryId parameter is used to handle callback queries when applicable (optional).
     * @note By default, web page previews for links in the message are not disabled (optional).
     */
    bool sendSpecificMessage(const QVariant &chatId,
                             const QString& text,
                             const qTbot::ExtraJsonObjects &extraObjects = {},
                             const QString &callBackQueryId = {},
                             unsigned long long replyToMessageId = 0,
                             const QString &parseMode = "html",
                             bool disableWebPagePreview = false);

    /**
     * @brief Sends a specific message with a custom keyboard to a chat.
     *
     * This function sends a specific message to a chat with a custom keyboard. The message can contain text and additional settings to customize its behavior.
     *
     * @param chatId The unique identifier of the chat to send the message to.
     * @param text The text content of the message to be sent.
     * @param keyboard A list of maps where each map represents a button with a callback function.
     * @param callBackQueryId The unique identifier for callback queries triggered by the message (optional).
     * @param replyToMessageId The unique identifier of the message to reply to, if any (optional).
     * @param parseMode Sets a text parsing mode. supports markdown and html,
     *  by default will be used html mode. If you want to disable parsing mode sets this option to empty string.
     * @param disableWebPagePreview Set to true to disable web page previews for links in the message (optional).
     *
     * @return Returns true if the message was sent successfully, false otherwise.
     *
     * @note The keyboard parameter should be a list of maps where each map represents a button.
     *  The button's label is the map key, and the associated callback function is the map value.
     * @note The callBackQueryId parameter is used to handle callback queries when buttons are pressed (optional).
     * @note By default, web page previews for links in the message are not disabled (optional).
     */
    bool sendSpecificMessageWithKeyboard(const QVariant &chatId,
                                         const QString& text,
                                         const KeyboardOnMessage &keyboard,
                                         const QString &callBackQueryId = "",
                                         unsigned long long replyToMessageId = 0,
                                         const QString &parseMode = "html",
                                         bool disableWebPagePreview = false);

    /**
     * @brief Sends a specific message with a custom keyboard to a chat.
     *
     * This function sends a specific message to a chat with a custom keyboard.
     *  The message can contain text and additional settings to customize its behavior.
     *
     * @param chatId The unique identifier of the chat to send the message to.
     * @param text The text content of the message to be sent.
     * @param keyboard A list of lists containing the keyboard buttons to display.
     * @param callBackQueryId The unique identifier for callback queries triggered by the message.
     * @param onTimeKeyboard Set to true to display the keyboard only once.
     * @param autoResizeKeyboard Set to true to automatically resize the keyboard.
     * @param replyToMessageId The unique identifier of the message to reply to, if any.
     * @param parseMode Sets a text parsing mode. supports markdown and html,
     *  by default will be used html mode. If you want to disable parsing mode sets this option to empty string.
     * @param disableWebPagePreview Set to true to disable web page previews for links in the message.
     *
     * @return Returns true if the message was sent successfully, false otherwise.
     *
     * @note The keyboard parameter should be a list of lists of strings representing keyboard buttons.
     * @note The callBackQueryId parameter is used to handle callback queries when buttons are pressed.
     * @note By default, web page previews for links in the message are not disabled.
     */
    bool sendSpecificMessageWithKeyboard(const QVariant &chatId,
                                         const QString& text,
                                         const QList<QList<QString> > &keyboard,
                                         const QString &callBackQueryId = "",
                                         bool onTimeKeyboard = false,
                                         bool autoResizeKeyboard = true,
                                         unsigned long long replyToMessageId = 0,
                                         const QString &parseMode = "html",
                                         bool disableWebPagePreview = false);

    bool deleteMessage(const QVariant& chatId, const QVariant& messageId) override;

    /**
     * @brief Edits a specific message with a custom keyboard in a chat.
     *
     * This function allows you to edit a specific message in a chat with a custom keyboard. You can update the message's text and customize its behavior as needed.
     *
     * @param messageId The unique identifier of the message to edit.
     * @param chatId The unique identifier of the chat containing the message.
     * @param newText The new text content for the message.
     * @param parseMode Sets a text parsing mode. supports markdown and html,
     *  by default will be used html mode. If you want to disable parsing mode sets this option to empty string.
     * @param disableWebPagePreview Set to true to disable web page previews for links in the new text (optional).
     * @param keyboard A list of lists containing the new keyboard buttons to display (optional).
     * @param callBackQueryId The unique identifier for callback queries triggered by the edited message (optional).
     * @param onTimeKeyboard Set to true to display the keyboard only once (optional).
     * @param autoResizeKeyboard Set to true to automatically resize the keyboard (optional).
     *
     * @return Returns true if the message was successfully edited, false otherwise.
     *
     * @note The keyboard parameter should be a list of lists of strings representing keyboard buttons (optional).
     * @note The callBackQueryId parameter is used to handle callback queries when buttons are pressed (optional).
     * @note By default, web page previews for links in the new text are not disabled (optional).
     */
    bool editSpecificMessageWithKeyboard(const QVariant &messageId,
                                         const QVariant &chatId,
                                         const QString &newText,
                                         const QString &parseMode = "html",
                                         bool disableWebPagePreview = false,
                                         const QList<QList<QString> > &keyboard = {},
                                         const QString &callBackQueryId = "",
                                         bool onTimeKeyboard = false,
                                         bool autoResizeKeyboard = false);


    /**
     * @brief Edits a specific message with a custom keyboard in a chat.
     *
     * This function allows you to edit a specific message in a chat with a custom keyboard. You can update the message's text and customize its behavior as needed.
     *
     * @param messageId The unique identifier of the message to edit.
     * @param chatId The unique identifier of the chat containing the message.
     * @param text The new text content for the message.
     * @param parseMode Sets a text parsing mode. supports markdown and html,
     *  by default will be used html mode. If you want to disable parsing mode sets this option to empty string.
     * @param disableWebPagePreview Set to true to disable web page previews for links in the new text (optional).
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @param callBackQueryId The unique identifier for callback queries triggered by the edited message (optional).
     *
     * @return Returns true if the message was successfully edited, false otherwise.
     *
     * @note The keyboard parameter should be a list of maps where each map represents a button. The button's label is the map key, and the associated callback function is the map value (optional).
     * @note The callBackQueryId parameter is used to handle callback queries when buttons are pressed (optional).
     * @note By default, web page previews for links in the new text are not disabled (optional).
 */
    bool editSpecificMessageWithKeyboard(const QVariant& messageId,
                                         const QVariant &chatId,
                                         const QString &text,
                                         const QString &parseMode = "html",
                                         bool disableWebPagePreview = false,
                                         const KeyboardOnMessage &keyboard = {},
                                         const QString &callBackQueryId = "");

    /**
     * @brief Edits a keyboard of message in a chat.
     *
     * This function allows you to edit a keyboard of specific message.
     *
     * @param messageId The unique identifier of the message to edit.
     * @param chatId The unique identifier of the chat containing the message.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @param callBackQueryId The unique identifier for callback queries triggered by the edited message (optional).
     *
     * @return Returns true if the message was successfully edited, false otherwise.
     *
     * @note The keyboard parameter should be a list of maps where each map represents a button. The button's label is the map key, and the associated callback function is the map value (optional).
     * @note The callBackQueryId parameter is used to handle callback queries when buttons are pressed (optional).
     * @note By default, web page previews for links in the new text are not disabled (optional).
 */
    bool editMessageKeyboard(const QVariant& messageId,
                             const QVariant &chatId,
                             const KeyboardOnMessage &keyboard = {},
                             const QString &callBackQueryId = "");

    /**
     * @brief Edits a specific message in a chat.
     *
     * This function allows you to edit a specific message in a chat. You can update the message's text and customize its behavior as needed.
     *
     * @param messageId The unique identifier of the message to edit.
     * @param chatId The unique identifier of the chat containing the message.
     * @param newText The new text content for the message.
     * @param callBackQueryId The unique identifier for callback queries triggered by the edited message (optional).
     * @param parseMode Sets a text parsing mode. supports markdown and html,
     *  by default will be used html mode. If you want to disable parsing mode sets this option to empty string.
     * @param disableWebPagePreview Set to true to disable web page previews for links in the new text (optional).
     *
     * @return Returns true if the message was successfully edited, false otherwise.
     *
     * @note The callBackQueryId parameter is used to handle callback queries when applicable (optional).
     * @note By default, web page previews for links in the new text are not disabled (optional).
     */
    bool editSpecificMessage(const QVariant &messageId,
                             const QVariant &chatId,
                             const QString &newText,
                             const QString &callBackQueryId = {},
                             const QString &parseMode = "html",
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

    bool sendFile( const QFileInfo& file, const QVariant& chatId) override;

    bool sendFile( const QByteArray& file, const QString& fileName, const QVariant& chatId) override;

    /**
     * @brief sendPhoto This method will send image into chat with @a chatId
     * @param photo this is photo path.
     * @param chatId target chat
     * @param replyToMessageId The unique identifier of the message to reply to, if any.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @return true if photo will snt successful
     */
    bool sendPhoto(const QFileInfo& photo,
                   const QVariant& chatId,
                   const QString &description,
                   const QString &parseMode = "html",
                   unsigned long long replyToMessageId = 0,
                   const KeyboardOnMessage &keyboard = {});

    /**
     * @brief sendPhoto This method will send image into chat with @a chatId
     * @param photo this is photo data.
     * @param chatId target chat
     * @param fileName This is dispalyed name of photo.
     * @param replyToMessageId The unique identifier of the message to reply to, if any.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @return true if photo will snt successful
     */
    bool sendPhoto(const QByteArray& photo,
                   const QString& fileName,
                   const QVariant& chatId,
                   const QString &description, const QString &parseMode,
                   unsigned long long replyToMessageId = 0,
                   const KeyboardOnMessage &keyboard = {});

    /**
     * @brief sendFileWithDescription This method sents a byte array as a file into @a chatId with additional text @a description.
     * @param file This is a file source
     * @param fileName This is a dispalyed name of file.
     * @param chatId This is distanation id chat.
     * @param description additional text for message.
     * @return true if the message sents successful else false.
     */
    bool sendFileWithDescription(const QByteArray& file,
                                 const QString& fileName,
                                 const QVariant& chatId,
                                 const QString& description);

    /**
     * @brief sendFileWithDescription This method sents a byte array as a file into @a chatId with additional text @a description.
     * @param file This is a file source
     * @param chatId This is distanation id chat.
     * @param description additional text for message.
     * @return true if the message sents successful else false.
     */
    bool sendFileWithDescription( const QFileInfo& file,
                                 const QVariant& chatId,
                                 const QString& description);
    /**
     * @brief sendFileById This is specific method of the telegram bot. sents file by id.
     * @param fileID This is file id.
     * @param chatId chat that should receive a file.
     * @return true if the file sent successful.
     */
    bool sendFileById(const QString& fileID, const QVariant& chatId);

    /**
     * @brief sendLocation This method sents locatin to user.
     * @param chatId This is distanation id chat.
     * @param latitude
     * @param longitude
     * @param replyToMessageId The unique identifier of the message to reply to, skip if you want to sent new independet message.
     * @return true if locations sent successful else false
     */
    bool sendLocation(const QVariant& chatId,
                      const QString& text,
                      float latitude,
                      float longitude,
                      unsigned long long replyToMessageId = 0);

    // to do

    // * forwardMessage implementations
    // * copyMessage implementations
    // * sendPhoto implementations
    // * sendAudio implementations
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

    /**
     * @brief gelLastMessageId this method returns last sendet message id.
     * @param chatId chat id, when you want to get last message id.
     * @return message id.
     */
    int gelLastMessageId(unsigned long long &chatId) const;

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

    /**
     * @brief sendMessageRequest This method invoke when bot will be sent eny messages into chat.
     * @param rquest This is a message request.
     * @return true if the message sent successful else false.
     */
    virtual bool sendMessageRequest(const QSharedPointer<iRequest> &rquest);

private slots:
    void handleLogin();
    void handleLoginErr(QNetworkReply::NetworkError err);
    void handleFileHeader(const QWeakPointer<QNetworkReply>& sender,
                          const QWeakPointer<iFile> &receiver);

private:


    bool sendFileWithPrivate(const QSharedPointer<TelegramSendFile>& file);

    QString findFileInlocatStorage(const QString& fileId) const;
    QHash<QString, QSharedPointer<QJsonObject> >
    prepareInlineKeyBoard(const KeyboardOnMessage &keyboard);
    ExtraJsonObjects prepareKeyboard(bool autoResizeKeyboard,
                                     bool onTimeKeyboard,
                                     const QList<QList<QString> > &keyboard);

    unsigned long long _id = 0;
    QString _username;
    QSharedPointer<QNetworkReply> _loginReplay;
    QMap<QString, std::function<void(const QString&, const QVariant&)>> _handleButtons;

    QHash<unsigned long long, int> _lastMessageId;

    QHash<QString, QSharedPointer<TelegramFile>> _filesMetaInfo;


};
}
#endif // ITELEGRAMBOT_H
