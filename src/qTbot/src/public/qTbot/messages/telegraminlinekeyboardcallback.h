//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMINLINEKEYBOARDCALLBACK_H
#define TELEGRAMINLINEKEYBOARDCALLBACK_H

#include <qTbot/ijsonbasedobject.h>

namespace qTbot {

/**
 * @brief The TelegramInlineKeyBoardCallBack class
 */
class QTBOT_EXPORT TelegramInlineKeyBoardCallBack: public IJsonBasedObject
{
public:
    TelegramInlineKeyBoardCallBack();
    TelegramInlineKeyBoardCallBack(const QJsonObject &jsonObject);

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
     * @brief callBackData line of the call back that was be clicked.
     * @return line of the call back that was be clicked.
     */
    QString callBackData() const;

    /**
     * @brief messageId id of the message when was be presed button.
     * @return id of the message when was be presed button.
     */
    QVariant messageId() const;

};
}
#endif // TELEGRAMINLINEKEYBOARDCALLBACK_H
