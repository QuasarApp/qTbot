//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef ITELEGRAMBOT_H
#define ITELEGRAMBOT_H

#include "ibot.h"

namespace qTbot {

/**
 * @brief The ITelegramBot class This is base implementation of the all telegramm bots.
 */
class QTBOT_EXPORT ITelegramBot : public IBot
{
public:
    ITelegramBot();

    bool login(const QByteArray &token) override;

protected:
    /**
     * @brief makePrefix This method prepare a prefix message for all telegramm bots.
     * @return telegramm request prefix/
     */
    QByteArray makePrefix() const;

private:
    QNetworkReques request;

};
}
#endif // ITELEGRAMBOT_H
