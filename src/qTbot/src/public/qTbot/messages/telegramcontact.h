//#
//# Copyright (C) 2023-2026 QuasarApp.
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
    /**
     * @brief TelegramContact default constructor.
     */
    TelegramContact();

    /**
     * @brief Constructs a Contact object from a JSON object.
     * @param jsonObject The JSON object containing contact data.
     */
    TelegramContact(const QJsonObject &jsonObject);

    /**
     * @brief userIdInt This is the numeric id of the user contact.
     * @return id of the user
     */
    unsigned long long userIdInt() const;

    /**
     * @brief userId This is the id of the user contact.
     * @return id of the user
     */
    QVariant userId() const;

    /**
     * @brief firstName Returns the first name of the contact.
     * @return The first name of the contact.
     */
    QString firstName() const;

    /**
     * @brief lastName Returns the last name of the contact.
     * @return The last name of the contact.
     */
    QString lastName() const;

    /**
     * @brief username Returns the username of the contact.
     * @return The username of the contact.
     */
    QString username() const;

    /**
     * @brief phone Returns the phone number of the contact.
     * @return The phone number of the contact.
     */
    QString phone() const;

    /**
     * @brief languageCode Returns the language code of the contact.
     * @return The language code of the contact.
     */
    QString languageCode() const;
};
}
#endif // TELEGRAMCONTACT_H
