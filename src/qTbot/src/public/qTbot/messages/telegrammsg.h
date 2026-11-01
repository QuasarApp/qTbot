//#
//# Copyright (C) 2023-2026 QuasarApp.
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
 * @brief The TelegramMsg class This class provides the general messages of telegram.
 * The message object can contain text, geo data or a link to a video or image. All this data can be contained in one object.
 */
class QTBOT_EXPORT TelegramMsg: public iMessage
{
public:

    /**
     * @brief The QualitySelector enum This is the behavior of image and video selection.
     */
    enum QualitySelector {
        /**
         * @brief AroundSize This selection tries to find a file similar by size quality. For example,
         * we have an image with sizes [10, 100, 1000, 10000] kbytes - the invoke image(90) returns the image with size 100, because it is more similar by quality.
         */
        AroundSize = 0,
        /**
         * @brief BestOf This selection tries to find the best image with a size limit. For example,
         * we have an image with sizes [10, 100, 1000, 10000] kbytes - the invoke image(90) returns the image with size 10, because it is the maximum quality from 0 to 90 kbytes. If we invoke this method with a 2500 limitation, the function will return the image with size 1000.
         */
        BestOf = 1,
        /**
         * @brief Best This selection returns the best image of the available ones.
         */
        Best = 2,
        /**
         * @brief Fast This selection returns the fastest image of the available ones (minimum size).
         */
        Fast = 3
    };

    /**
     * @brief Type This is a string value of the telegram message types.
     */
    using Type = QString;

    /**
     * @brief Text This is the text type of the message.
     */
    const Type Text = "text";

    /**
     * @brief Image This is the image type of the telegram.
     */
    const Type Image = "photo";

    /**
     * @brief Document This is the type of the documents.
     */
    const Type Document = "document";

    /**
     * @brief Contact This is type of the files.
     */
    const Type Contact = "contact";

    /**
     * @brief Location This is the type of location data.
     */
    const Type Location = "location";

    /**
     * @brief Audio This is the type of audio files.
     */
    const Type Audio = "audio";

    /**
     * @brief TelegramMsg default constructor.
     */
    TelegramMsg();

    /**
     * @brief Constructs a Message object from a JSON object.
     * @param obj The JSON object containing message data.
     */
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
     * @brief date returns the date of the sent message.
     * @return message date.
     */
    qint64 date() const;

    /**
     * @brief text returns text that contains this message object.
     * @return text of message.
     */
    QString text() const;

    /**
     * @brief fullText Returns the text + caption value.
     * @return the text + caption value.
     */
    QString fullText() const;

    /**
     * @brief caption Returns only the caption value.
     * @return only the caption value.
     */
    QString caption() const;

    /**
     * @brief contains This method returns true if the message contains the chosen data type.
     * @param type This is the name of the type
     * @return true if the chosen type is available in this message.
     */
    bool contains(const Type& type);

    /**
     * @brief images This function returns an array of available image qualities
     * @return an array of available image qualities
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
     * @brief documents This method returns the contained document data.
     * @return the document description data.
     */
    QSharedPointer<TelegramDocument> documents() const;

    /**
     * @brief audio This method returns the contained audio data.
     * @return the audio description data.
     */
    QSharedPointer<TelegramAudio> audio() const;

    /**
     * @brief contact Returns the contact data.
     * @return the contact information.
     */
    QSharedPointer<TelegramContact> contact() const;

    unsigned long long updateId() const override;

    /**
     * @brief location Returns the location object of the message.
     * @return the location object.
     */
    QSharedPointer<TelegramLocation> location() const;
};

}
#endif // TELEGRAMMSG_H
