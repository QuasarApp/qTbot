//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMCONTACT_H
#define TELEGRAMCONTACT_H

#include <qTbot/ijsonbasedobject.h>

namespace qTbot {

/**
 * @brief The telegramcontact class contains information about user contact.
 */
class QTBOT_EXPORT TelegramContact: public IJsonBasedObject
{
public:
    TelegramContact();
    TelegramContact(const QJsonObject &jsonObject);

    /**
     * @brief userId This is id of usercontact
     * @return id of user
     */
    unsigned long long userIdInt() const;

    /**
     * @brief userId This is id of usercontact
     * @return id of user
     */
    QVariant userId() const;

    /**
     * @brief chatFirstName returns the first participant's first name in the chat.
     * @return The first participant's first name in the chat.
     */
    QString firstName() const;

    /**
     * @brief chatLastName returns the first participant's last name in the chat.
     * @return The first participant's last name in the chat.
     */
    QString lastName() const;

    /**
     * @brief chatUsername returns the first participant's username in the chat.
     * @return The first participant's username in the chat.
     */
    QString username() const;

    /**
     * @brief chatUsername returns the first participant's username in the chat.
     * @return The first participant's username in the chat.
     */
    QString phone() const;

    /**
     * @brief languageCode returns the sender's language code.
     * @return The sender's language code.
     */
    QString languageCode() const;
};
}
#endif // TELEGRAMCONTACT_H
