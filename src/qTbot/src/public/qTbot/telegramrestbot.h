//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMRESTBOT_H
#define TELEGRAMRESTBOT_H

#include "itelegrambot.h"

class QTimer;

namespace qTbot {

/**
 * @brief The TelegramRestBot class Is the rest implementation base on the getUpdates (long polling) telegram method.
 * The bot receives all updates from the telegram server by requesting them periodically.
 */
class QTBOT_EXPORT TelegramRestBot: public ITelegramBot
{
    Q_OBJECT
public:
    /**
     * @brief TelegramRestBot default constructor.
     */
    TelegramRestBot();

    /**
     * @brief ~TelegramRestBot destructor. Stops the update polling.
     */
    ~TelegramRestBot();

    // IBot interface
    /**
     * @brief login This method gets basic information of the bot from the remote server
     * and starts the long polling of the updates.
     * @param token This is the token value for login
     * @return true if the login request was sent successfully else false.
     */
    bool login(const QByteArray &token) override;

    /**
     * @brief logout This method stops the long polling of the updates and removes the login token of the bot.
     */
    void logout() override;

    /**
     * @brief updateDelay This is the interval "how many msecs the bot will wait to send the next request for updates". By default it is 1000 msecs.
     * @return the delay of the updates in milliseconds.
     */
    int updateDelay() const;

    /**
     * @brief setUpdateDelay This method sets a new value for the TelegramRestBot::updateDelay property.
     * @param newUpdateDelay This is the new value of the TelegramRestBot::updateDelay property.
     */
    void setUpdateDelay(int newUpdateDelay);

    /**
     * @brief setProcessed This method sets a new list of processed updates.
     * The bot will start to receive the updates from the first not processed update.
     * @param newProcessed This is the new list of processed updates.
     */
    void setProcessed(const QSet<unsigned long long> &newProcessed) override;
private slots:
    void handleReceiveUpdates(const QByteArray &replay);
    void handleReceiveUpdatesErr(QNetworkReply::NetworkError err);

private:
    void startUpdates();

    bool _run = false;
    long long _lanstUpdateTime = 0;
    unsigned long long _lanstUpdateid = 0;

    int _updateDelay = 1000;

};
}
#endif // TELEGRAMRESTBOT_H
