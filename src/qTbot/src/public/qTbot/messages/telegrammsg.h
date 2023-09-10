//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMMSG_H
#define TELEGRAMMSG_H

#include "itelegrammessage.h"

namespace qTbot {

/**
 * @brief The TelegramMsg class This class provide general mesasges of telegram.
 * The message object can contains text, geo or link to video,image. all this dates can be contains in one object.
 */
class QTBOT_EXPORT TelegramMsg: public ITelegramMessage
{
public:
    /**
     * @brief Type just string value of the telegram messages types.
     */
    using Type = QString;

    /**
     * @brief Text This is text type of the message.
     */
    const Type Text = "text";

    /**
     * @brief Image This is image type of the telegram
     */
    const Type Image = "photo";

    /**
     * @brief Document This is type of the files.
     */
    const Type Document = "document";

    /**
     * @brief Audio This is type of Audio files.
     */
    const Type Audio = "audio";

    TelegramMsg();


    /**
     * @brief messageId returns the message ID.
     * @return The message ID.
     */
    int messageId() const;

    /**
     * @brief fromId returns the sender's ID.
     * @return The sender's ID.
     */
    int fromId() const;

    /**
     * @brief isBot checks if the sender is a bot.
     * @return true if the sender is a bot, false otherwise.
     */
    bool isBot() const;

    /**
     * @brief firstName returns the sender's first name.
     * @return The sender's first name.
     */
    QString firstName() const;

    /**
     * @brief lastName returns the sender's last name.
     * @return The sender's last name.
     */
    QString lastName() const;

    /**
     * @brief username returns the sender's username.
     * @return The sender's username.
     */
    QString username() const;

    /**
     * @brief languageCode returns the sender's language code.
     * @return The sender's language code.
     */
    QString languageCode() const;

    /**
     * @brief chatId returns the chat ID.
     * @return The chat ID.
     */
    int chatId() const;

    /**
     * @brief chatFirstName returns the first participant's first name in the chat.
     * @return The first participant's first name in the chat.
     */
    QString chatFirstName() const;

    /**
     * @brief chatLastName returns the first participant's last name in the chat.
     * @return The first participant's last name in the chat.
     */
    QString chatLastName() const;

    /**
     * @brief chatUsername returns the first participant's username in the chat.
     * @return The first participant's username in the chat.
     */
    QString chatUsername() const;

    /**
     * @brief chatType returns the chat type.
     * @return The chat type.
     */
    QString chatType() const;

    /**
     * @brief date returns date of the snet message.
     * @return message date.
     */
    qint64 date() const;

    /**
     * @brief text returns text that contains this message object.
     * @return text of message.
     */
    QString text() const;

    /**
     * @brief contains This method returns true if the message contains choosed data type.
     * @param type This is name of the type
     * @return true if the choosed type is available in this message.
     */
    bool contains(const Type& type);

    /**
     * @brief image This function returns array of available images qualites
     * @return array of available images qualites
     */
    QJsonArray image() const;

    /**
     * @brief imageUId This method returns unique ID of the image.
     *  If the maximumSize will be skipped, this function chooses image with maximum quality.
     * @param maximumSize This is limitation for the size of image.
     * @return unique id of the choosed image.
     */
    QString imageUId(int maximumSize = -1) const;


    QList<> documents() const;

};

}
#endif // TELEGRAMMSG_H
