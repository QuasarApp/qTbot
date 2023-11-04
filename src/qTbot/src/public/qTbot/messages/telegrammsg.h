//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMMSG_H
#define TELEGRAMMSG_H

#include "imessage.h"
#include "qTbot/messages/telegramcontact.h"
#include "telegramaudio.h"
#include "telegramdocument.h"
#include "telegramlocation.h"
#include "qTbot/messages/telegramimage.h"

namespace qTbot {

/**
 * @brief The TelegramMsg class This class provide general mesasges of telegram.
 * The message object can contains text, geo or link to video,image. all this dates can be contains in one object.
 */
class QTBOT_EXPORT TelegramMsg: public iMessage
{
public:

    /**
     * @brief The QualitySelector enum This is behavior of image and video selection.
     */
    enum QualitySelector {
        /// This selection try to find file similar by size qulity. For example
        /// we have a image with [10, 100, 1000, 10000] kbytes sizes - The invoke image(90) returns iamge with size 100 because it is more similar by quality image.
        AroundSize = 0,
        /// This selection try to find best image with size limit. For example
        /// we have a image with [10, 100, 1000, 10000] kbytes sizes - The invoke image(90) returns iamge with size 10 because it is maximum quality from the 0 to 90 kbytes. If we invoke this method with 2500 limitation then function will return iamge with quality 1000.

        BestOf = 1,
        /// This selection returns best iamge of available.
        Best = 2,
        /// This selection returns faster iamge of available. (minimum size)
        Fast = 3
    };

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
     * @brief Contact This is type of the files.
     */
    const Type Contact = "contact";

    /**
     * @brief Location This is type of location data.
     */
    const Type Location = "location";

    /**
     * @brief Audio This is type of Audio files.
     */
    const Type Audio = "audio";

    TelegramMsg();

    TelegramMsg(const QJsonObject& obj);

    /**
     * @brief messageId returns the message ID.
     * @return The message ID.
     */
    unsigned long long messageId() const override;

    /**
     * @brief fromId returns the sender's ID.
     * @return The sender's ID.
     */
    unsigned long long fromId() const;

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
    QVariant chatId() const override;

    bool isValid() const override;

    QString from() const override;

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
     * @brief images This function returns array of available images qualites
     * @return array of available images qualites
     */
    QList<QSharedPointer<TelegramImage>> images() const;

    /**
     * @brief Retrieve an image from the Telegram service with specified quality and size parameters.
     *
     * This method allows you to request an image from the Telegram service with a specific quality selection behavior.
     * You can control the image selection behavior by providing a QualitySelector enum value, and optionally, a maximum size limit.
     *
     * @param behavior (Optional) The QualitySelector enum value that defines the image selection behavior. Defaults to `AroundSize` if not specified.
     *   - `AroundSize`: Attempts to find an image with similar quality based on size.
     *   - `BestOf`: Tries to find the best image within a size limit.
     *   - `Best`: Retrieves the best available image.
     *   - `Fast`: Retrieves the fastest available image (minimum size).
     *
     * @param size (Optional) The required size for the image (in bytes). Defaults to 100,000 bytes if not specified.
     *
     * @return A TelegramImage object representing the selected image.
     */
    QSharedPointer<TelegramImage> image(QualitySelector behavior = AroundSize, int size = 100000) const;

    /**
     * @brief documents This method returns contained document data.
     * @return document description data.
     */
    QSharedPointer<TelegramDocument> documents() const;

    /**
     * @brief audio This method returns contained audio data.
     * @return audio description data.
     */
    QSharedPointer<TelegramAudio> audio() const;

    /**
     * @brief contact return contact
     * @return contact information
     */
    QSharedPointer<TelegramContact> contact() const;

    unsigned long long updateId() const override;

    /**
     * @brief location returns location object of message.
     * @return location object.
     */
    QSharedPointer<TelegramLocation> location() const;
};

}
#endif // TELEGRAMMSG_H
