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
     * @brief interval This is interval "how often bot will be check updates on the telegram server" By defaul is 1 second.
     * @return interval of the updates.
     */
    int interval() const;

    /**
     * @brief setInterval This method sets new value for the TelegramRestBot::interval property.
     * @param newInterval This is new value of the TelegramRestBot::interval property.
     */
    void setInterval(int newInterval);

private slots:
    void handleTimeOut();

private:

    QTimer *_timer = nullptr;
};
}
#endif // TELEGRAMRESTBOT_H
