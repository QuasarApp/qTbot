//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef ITELEGRAMBOT_H
#define ITELEGRAMBOT_H

#include "file.h"
#include "ibot.h"
#include "virtualfile.h"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

namespace qTbot {

class ITelegramMessage;
class TelegramFile;

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
     * bool result = sendMessage(chatId, "Check)", 0, true, true);
     * @endcode
     */
    bool sendSpecificMessage(const QVariant &chatId,
                             const QString& text,
                             unsigned long long replyToMessageId = 0,
                             bool markdown = true,
                             bool disableWebPagePreview = false,
                             const Responce& cb = {});


    QSharedPointer<iFile> getFile(const QString& fileId, iFile::Type fileType = iFile::Type::Ram) override;

    /**
     * @brief Get a file by its ID.
     *
     * This function allows you to retrieve a file by its ID.
     *
     * @param fileId The ID of the file to retrieve.
     * @param cb The callback function to be called after the file is retrieved.
     *          The function takes a shared_ptr to a File object as a parameter.
     * @return Returns true if the file retrieval operation was successfully initiated and false in case of an error.
     */
    bool getFile(const QString& fileId, std::function<void(const QSharedPointer<File>&)> cb);

    /**
     * @brief Get a virtual file by its ID.
     *
     * This function allows you to retrieve a virtual file by its ID.
     *
     * @param fileId The ID of the virtual file to retrieve.
     * @param cb The callback function to be called after the virtual file is retrieved.
     *          The function takes a shared_ptr to a VirtualFile object as a parameter.
     * @return Returns true if the virtual file retrieval operation was successfully initiated and false in case of an error.
     */
    bool getFile(const QString& fileId, std::function<void(const QSharedPointer<VirtualFile>&)> cb);


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

    /**
     * @brief makePrefix This method prepare a prefix message for all telegramm bots.
     * @return telegramm request prefix/
     */
    QByteArray makePrefix() const override;

    size_t sendRequest(const QSharedPointer<iRequest>& rquest, const Responce& cb) override;
    QSharedPointer<QNetworkReply> sendRequest(const QSharedPointer<iRequest>& rquest) override;

    /**
     * @brief getFileSizeByUniqueId This method return size of the file by id
     * @param id This is id of required file.
     * @return file size - else 0
     */
    int getFileSizeByUniqueId(const QString& id) const;

    void incomeNewMessage(const QSharedPointer<iMessage>& msg) override;
private:
    QString findFileInlocatStorage(const QString& fileId) const;
    void extractAllMetaInfoFromUpdate(const QSharedPointer<iMessage> &answer);

    unsigned long long _id = 0;
    QString _username;

    QNetworkAccessManager *_manager = nullptr;

    QHash<QString, QSharedPointer<TelegramFile>> _filesMetaInfo;


};
}
#endif // ITELEGRAMBOT_H
