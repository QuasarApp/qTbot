//#
//# Copyright (C) 2023-2023 QuasarApp.
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
 * @brief The TelegramRestBot class Is Rest implementation base on the Update API telegram method
 */
class QTBOT_EXPORT TelegramRestBot: public ITelegramBot
{
    Q_OBJECT
public:
    TelegramRestBot();
    ~TelegramRestBot();

    // IBot interface
    bool login(const QByteArray &token);


    /**
     * @brief updateDelay This is interval "how many msec bot will be wait for sent next request of updates" By defaul is 1000 msecs.
     * @return a delay of update.
     */
    int updateDelay() const;

    /**
     * @brief setUpdateDelay This method sets new value for the TelegramRestBot::updateDelay property.
     * @param newUpdateDelay This is new value of the TelegramRestBot::updateDelay property.
     */
    void setUpdateDelay(int newUpdateDelay);

private slots:
    void handleReceiveUpdates(const QWeakPointer<QNetworkReply>& replay);
    void handleReceiveUpdatesErr(QNetworkReply::NetworkError err);

private:
    void startUpdates();

    long long _lanstUpdateTime = 0;
    int _updateDelay = 1000;

};
}
#endif // TELEGRAMRESTBOT_H
