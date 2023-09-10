//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef ITELEGRAMMESSAGE_H
#define ITELEGRAMMESSAGE_H

#include "imessage.h"
#include "qjsonobject.h"

namespace qTbot {

/**
 * @brief The ItelegramMessage class This is base interface of the all telegram messages.
 */
class QTBOT_EXPORT ITelegramMessage: public iMessage
{
public:
    ITelegramMessage();

    // iMessage interface
public:
    bool isValid() const override;
    QByteArray makeUpload() const override;

    /**
     * @brief rawJson Telegram use rest api with json objects. So all received messages will be parsed in to jsobject.
     * @return js implementation of object.
     */
    const QJsonObject& rawJson() const;

    /**
     * @brief setRawJson this method convert jsobject into telegram message.
     * @param newRawJson new data for telegram message.
     */
    virtual void setRawJson(const QJsonObject &newRawJson);

    void setRawData(const QByteArray &newRawData) override;

    /**
     * @brief result This is result filed of thetelegram responce.
     * @return json value of the resul field.
     */
    QJsonValue result() const;

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


protected:
    /**
     * @brief rawJsonObject This is inner method for getting raw json object (rad only)
     * @return read only json object.
     */
    const QJsonObject& rawJsonObject() const;
private:
    QJsonObject _rawJson;

};

}
#endif // ITELEGRAMMESSAGE_H
