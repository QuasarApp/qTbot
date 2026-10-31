//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef ITELEGRAMBOT_H
#define ITELEGRAMBOT_H

#include "ibot.h"
#include "qTbot/telegramargs.h"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

namespace qTbot {

class ITelegramMessage;
class TelegramFile;
class TelegramUpdateAnswer;
class TelegramSendFile;
class TelegramSingleRquest;

/**
 * @brief ButtonCB callback type for inline keyboard buttons.
 * It is invoked with the button key and the id of the message that contains the button.
 */
typedef std::function<void(const QString& buttonKey, const QVariant& msgID)> ButtonCB;

/**
 * @brief KeyboardOnMessage type. A list of rows where each row is a map of
 * button keys to the callback function that is invoked when the button is pressed.
 */
typedef QList<QHash<QString, ButtonCB >> KeyboardOnMessage;

/**
 * @brief The ITelegramBot class This is the base implementation of all telegram bots.
 */
class QTBOT_EXPORT ITelegramBot : public IBot
{
    Q_OBJECT
public:
    /**
     * @brief ITelegramBot default constructor.
     */
    ITelegramBot();

    /**
     * @brief ~ITelegramBot destructor.
     */
    ~ITelegramBot();

    /**
     * @brief login This method gets basic information of the bot from the remote server.
     * @param token This is the token value for login
     * @return true if the login request was sent successfully else false.
     */
    bool login(const QByteArray &token) override;

    /**
     * @brief sendMessage This method sends text to the selected chat.
     * @param chatId This is the selected chat id
     * @param text This is the text that needs to be sent.
     * @param priority This is the priority of the request in the send queue.
     * @return true if the data was sent successfully else false.
     */
    bool sendMessage(const QVariant &chatId,
                     const QString& text,
                     iRequest::RequestPriority priority = iRequest::NormalPriority) override;

    /**
     * @brief sendLocationRequest This method sends into the chat a button that will automatically send the geo location to the bot.
     * @param chatId This is the chat id where the request will be sent.
     * @param text This is the message text.
     * @param buttonText This is the text on the button.
     * @param onetimeKeyboard If true the keyboard will be removed after the first usage.
     * @return true if the request was sent successfully else false.
     */
    bool sendLocationRequest(const QVariant &chatId, const QString& text, const QString &buttonText, bool onetimeKeyboard);

    /**
     * @brief sendSelfContactRequest This method sends into the chat a button that will automatically send the user contact information to the bot.
     * @param chatId This is the chat id where the request will be sent.
     * @param text This is the message text.
     * @param buttonText This is the text on the button.
     * @param onetimeKeyboard If true the keyboard will be removed after the first usage.
     * @return true if the request was sent successfully else false.
     */
    bool sendSelfContactRequest(const QVariant &chatId, const QString& text, const QString &buttonText, bool onetimeKeyboard);

    /**
     * @brief Sends a specific message to a chat.
     *
     * This function sends a specific message to a chat. You can include text and additional objects as needed to customize the message's content and behavior.
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @param extraObjects A map containing additional objects associated with the message (optional).
     *
     * @return Returns true if the message was sent successfully, false otherwise.
     *
     * @note The extraObjects parameter is a map where each key represents the object's name, and the associated value is a shared pointer to a JSON object (optional).
     */
    bool sendSpecificMessage(const TelegramArgs& args,
                             const qTbot::ExtraJsonObjects &extraObjects = {});

    /**
     * @brief Sends a specific message with a custom keyboard to a chat.
     * This function sends a specific message to a chat with a custom keyboard. The message can contain text and additional settings to customize its behavior.
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @param keyboard A list of maps where each map represents a button with a callback function.
     * @return Returns true if the message was sent successfully, false otherwise.
     *
     * @note The keyboard parameter should be a list of maps where each map represents a button.
      *  The button's label is the map key, and the associated callback function is the map value.
     */
    bool sendSpecificMessageWithKeyboard(const TelegramArgs& args,
                                         const KeyboardOnMessage &keyboard);

    /**
     * @brief Sends a specific message with a custom keyboard to a chat.
     *
     * This function sends a specific message to a chat with a custom keyboard.
      *  The message can contain text and additional settings to customize its behavior.
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @param keyboard A list of lists containing the keyboard buttons to display.
     * @param onTimeKeyboard Set to true to display the keyboard only once.
     * @param autoResizeKeyboard Set to true to automatically resize the keyboard.
     *
     * @return Returns true if the message was sent successfully, false otherwise.
     *
     * @note By default, web page previews for links in the message are not disabled.
     */
    bool sendSpecificMessageWithKeyboard(const TelegramArgs& args,
                                         const QList<QList<QString> > &keyboard,
                                         bool onTimeKeyboard = false,
                                         bool autoResizeKeyboard = true);

    /**
     * @brief deleteMessage This is the main method to delete messages.
     * @param chatId This is the chat id where the message will be removed.
     * @param messageId This is the removed message id.
     * @return true if the request was prepared successfully
     */
    bool deleteMessage(const QVariant& chatId, const QVariant& messageId) override;

    /**
     * @brief Edits a specific message with a custom keyboard in a chat.
     *
     * This function allows you to edit a specific message in a chat with a custom keyboard. You can update the message's text and customize its behavior as needed.
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @param messageId The unique identifier of the message to edit.
     * @param keyboard A list of lists containing the new keyboard buttons to display (optional).
     * @param onTimeKeyboard Set to true to display the keyboard only once (optional).
     * @param autoResizeKeyboard Set to true to automatically resize the keyboard (optional).
     *
     * @return Returns true if the message was successfully edited, false otherwise.
     *
     * @note By default, web page previews for links in the new text are not disabled (optional).
     */
    bool editSpecificMessageWithKeyboard(const QVariant &messageId,
                                         const TelegramArgs& args,
                                         const QList<QList<QString> > &keyboard = {},
                                         bool onTimeKeyboard = false,
                                         bool autoResizeKeyboard = false);


    /**
     * @brief Edits a specific message with a custom keyboard in a chat.
     *
     * This function allows you to edit a specific message in a chat with a custom keyboard. You can update the message's text and customize its behavior as needed.
     *
     * @param messageId The unique identifier of the message to edit.
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     *
     * @return Returns true if the message was successfully edited, false otherwise.
     *
     * @note By default, web page previews for links in the new text are not disabled (optional).
     */
    bool editSpecificMessageWithKeyboard(const QVariant& messageId,
                                         const TelegramArgs& args,
                                         const KeyboardOnMessage &keyboard = {});

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
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @return Returns true if the message was successfully edited, false otherwise.
     *
     * @note By default, web page previews for links in the new text are not disabled (optional).
     */
    bool editSpecificMessage(const QVariant &messageId,
                             const TelegramArgs& args);

    /**
     * @brief getFile This method sends a request to get a file by id. The files can be saved into local storage if the type is chosen as Local.
     * @param fileId This is Telegram file id.
     * @param fileType this is type of file. Depending on this argument, the future will contain a different result: if it is the Local type, the future contains a link to the local file path, otherwise the file source as bytes.
     * @return a future with the file source or the path to the file, depending on the type.
     */
    QFuture<QByteArray> getFile(const QString& fileId, FileType fileType = FileType::Ram) override;

    /**
     * @brief getFileMeta This method receives the meta information of the file.
     * @param fileId This is id of the file.
     * @return future object with the result.
     */
    QFuture<QByteArray> getFileMeta(const QString& fileId);

    bool sendFile( const QFileInfo& file, const QVariant& chatId) override;

    bool sendFile( const QByteArray& file, const QString& fileName, const QVariant& chatId) override;

    /**
     * @brief sendFileMessage This method sends a message with a file.
     * @param file This is the path to the file that will be sent.
     * @param args This is general arguments of the message, include a chatID.
     * @return true if the message was sent successfully else false
     */
    bool sendFileMessage( const TelegramArgs& args, const QFileInfo& file);

    /**
     * @brief sendFileMessage This method sends a message with a file.
     * @param file This is the data that will be sent as a file with name @a fileName.
     * @param fileName This is name of the file.
     * @param args This is general arguments of the message, include a chatID.
     * @return true if the message was sent successfully else false
     */
    bool sendFileMessage( const TelegramArgs& args, const QByteArray& file, const QString& fileName);

    /**
     * @brief sendPhoto This method will send image into chat with @a chatId
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @param photo this is photo path.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @return true if the photo was sent successfully
     */
    bool sendPhoto(const TelegramArgs& args,
                   const QFileInfo& photo,
                   const KeyboardOnMessage &keyboard = {});

    /**
     * @brief sendPhoto This method will send image into chat with @a chatId
     * @param photo this is photo data.
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @param fileName This is displayed name of the photo.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @return true if the photo was sent successfully
     */
    bool sendPhoto(const TelegramArgs &args,
                   const QByteArray& photo,
                   const QString& fileName,
                   const KeyboardOnMessage &keyboard = {});

    /**
     * @brief sendFileById This is specific method of the telegram bot. sends a file by id.
     * @param fileID This is the file id.
     * @param chatId the chat that should receive the file.
     * @return true if the file was sent successfully.
     */
    bool sendFileById(const QString& fileID, const QVariant& chatId);

    /**
     * @brief sendLocation This method sends a location to the user.
     * @param args - This is a structure with general arguments of the telegram message.
      *  Use this structure to set the target and other arguments.
     * @param latitude This is the latitude of the location.
     * @param longitude This is the longitude of the location.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @return true if the location was sent successfully else false
     */
    bool sendLocation(const TelegramArgs &args,
                      float latitude,
                      float longitude,
                      const KeyboardOnMessage &keyboard = {});

    /**
     * @brief sendContact This method sends a contact data.
     * @param args the base arguments of the message.
     * @param firstName This is the first name of the contact.
     * @param phone This is the phone number of the contact.
     * @param secondName This is the second name of the user.
     * @return true if the contact was sent successfully
     */
    bool sendContact(const TelegramArgs &args,
                     const QString& phone,
                     const QString& firstName,
                     const QString& secondName = "");

    // to do

    // * forwardMessage implementations
    // * copyMessage implementations
    // * sendAudio implementations
    // * sendVideo implementations
    // * sendVoice implementations
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
     * @brief id This method returns the bot id number.
      * @returns the bot id number.
     */
    unsigned long long id() const;

    /**
     * @brief username This is the bot login
     * @returns the bot login.
     */
    const QString& username() const;

    /**
     * @brief gelLastMessageId this method returns last sent message id.
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
     * @return shared pointer to the meta information of the file. If the information does not exist, returns nullptr.
     */
    QSharedPointer<TelegramFile> getFileInfoByUniqueId(const QString& id) const;

    /**
     * @brief onRequestError This method invoked when the telegram server sends an error response. Default implementation just print error message on the console.
     * @param ansverWithError - This is the answer object with the error description and error codes.
     */
    virtual void onRequestError(const QSharedPointer<TelegramUpdateAnswer>& ansverWithError) const;

    void handleIncomeNewUpdate(const QSharedPointer<iUpdate> &) override;

    /**
     * @brief sendMessageRequest This method invoke when bot will be sends any messages into the chat.
     * @param rquest This is a message request.
     * @param msgIdCB call back function for the get a sent message id
     * @return true if the message sent successful else false.
     */
    virtual bool sendMessageRequest(const QSharedPointer<iRequest> &rquest,
                                    const std::function<void(int msgId)>& msgIdCB = {});

private slots:
    void handleLogin(const QByteArray &ansver);
    void handleLoginErr(QNetworkReply::NetworkError err);
    void handleFileHeader(const QByteArray &header);

private:

    QString findFileInlocatStorage(const QString& fileId) const;
    QHash<QString, QSharedPointer<QJsonObject> >
    prepareInlineKeyBoard(const KeyboardOnMessage &keyboard);
    ExtraJsonObjects prepareKeyboard(bool autoResizeKeyboard,
                                     bool onTimeKeyboard,
                                     const QList<QList<QString> > &keyboard);

    unsigned long long _id = 0;
    QString _username;
    QMap<QString, std::function<void(const QString&, const QVariant&)>> _handleButtons;

    QHash<unsigned long long, int> _lastMessageId;

    QHash<QString, QSharedPointer<TelegramFile>> _filesMetaInfo;


};
}
#endif // ITELEGRAMBOT_H
