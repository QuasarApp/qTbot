//#
//# Copyright (C) 2023-2025 QuasarApp.
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

    bool sendMessage(const QVariant &chatId,
                     const QString& text,
                     iRequest::RequestPriority priority = iRequest::NormalPriority) override;

    /**
     * @brief sendLocationRequest This method setn into chat button that will automaticaly sent geo location to bot.
     * @param chatId
     * @param text message text
     * @param buttonText Text on the button
     * @return true if request sents successfull else false.
     */
    bool sendLocationRequest(const QVariant &chatId, const QString& text, const QString &buttonText, bool onetimeKeyboard);

    /**
     * @brief sendSelfContactRequest This method sent into chat button that will automaticaly sent self contact information to bot.
     * @param chatId
     * @param text message text
     * @param buttonText Text on the button
     * @return true if request sents successfull else false.
     */
    bool sendSelfContactRequest(const QVariant &chatId, const QString& text, const QString &buttonText, bool onetimeKeyboard);

    /**
     * @brief Sends a specific message to a chat.
     *
     * This function sends a specific message to a chat. You can include text and additional objects as needed to customize the message's content and behavior.
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
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
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
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
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
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

    bool deleteMessage(const QVariant& chatId, const QVariant& messageId) override;

    /**
     * @brief Edits a specific message with a custom keyboard in a chat.
     *
     * This function allows you to edit a specific message in a chat with a custom keyboard. You can update the message's text and customize its behavior as needed.
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
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
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
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
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
     * @return Returns true if the message was successfully edited, false otherwise.
     *
     * @note By default, web page previews for links in the new text are not disabled (optional).
     */
    bool editSpecificMessage(const QVariant &messageId,
                             const TelegramArgs& args);

    /**
     * @brief getFile This method sent request to get a file by id. The files can be saved into local storage if the Type choosed as Local.
     * @param fileId This is Telegram file id.
     * @param fileType this is type of file. Depends of this argument future will be contains deffrent result if it is Local type then future will contains link to local file path else file source as bytes.
     * @return futur with file source or path to file depends of type.
     */
    QFuture<QByteArray> getFile(const QString& fileId, FileType fileType = FileType::Ram) override;

    /**
     * @brief getFileMeta This method receive meta information of the file.
     * @param fileId This is id of the file.
     * @return future objectl with result.
     */
    QFuture<QByteArray> getFileMeta(const QString& fileId);

    bool sendFile( const QFileInfo& file, const QVariant& chatId) override;

    bool sendFile( const QByteArray& file, const QString& fileName, const QVariant& chatId) override;

    /**
     * @brief sendFileMessage This method sents a message with file.
     * @param file This is path to sents file.
     * @param args This is general arguments of the message, include a chatID.
     * @return true if the message sents successful else false
     */
    bool sendFileMessage( const TelegramArgs& args, const QFileInfo& file);

    /**
     * @brief sendFileMessage This method sents a message with file.
     * @param file This is data that will be sents as a file with name @a fileName.
     * @param fileName This is name of the file.
     * @param args This is general arguments of the message, include a chatID.
     * @return true if the message sents successful else false
     */
    bool sendFileMessage( const TelegramArgs& args, const QByteArray& file, const QString& fileName);

    /**
     * @brief sendPhoto This method will send image into chat with @a chatId
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
     * @param photo this is photo path.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @return true if photo will snt successful
     */
    bool sendPhoto(const TelegramArgs& args,
                   const QFileInfo& photo,
                   const KeyboardOnMessage &keyboard = {});

    /**
     * @brief sendPhoto This method will send image into chat with @a chatId
     * @param photo this is photo data.
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
     * @param fileName This is dispalyed name of photo.
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @return true if photo will snt successful
     */
    bool sendPhoto(const TelegramArgs &args,
                   const QByteArray& photo,
                   const QString& fileName,
                   const KeyboardOnMessage &keyboard = {});

    /**
     * @brief sendFileById This is specific method of the telegram bot. sents file by id.
     * @param fileID This is file id.
     * @param chatId chat that should receive a file.
     * @return true if the file sent successful.
     */
    bool sendFileById(const QString& fileID, const QVariant& chatId);

    /**
     * @brief sendLocation This method sents locatin to user.
     * @param args - This is structure with general arguments of the tellegram message.
     *  Use This structure for sets target and another arguments.
     * @param latitude
     * @param longitude
     * @param keyboard A list of maps where each map represents a button with a callback function (optional).
     * @return true if locations sent successful else false
     */
    bool sendLocation(const TelegramArgs &args,
                      float latitude,
                      float longitude,
                      const KeyboardOnMessage &keyboard = {});

    /**
     * @brief sendContact This method sents a contact data.
     * @param args base arguments of message.
     * @param firstName This is first name of contact.
     * @param phone This is phone number of contact.
     * @param secondName This is second name of user.
     * @return true if contact sent successful
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
