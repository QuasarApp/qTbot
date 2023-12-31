//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSINGLERQUEST_H
#define TELEGRAMSINGLERQUEST_H

#include <qTbot/irequest.h>
#include <QVariant>
#include <QMap>

namespace qTbot {

/**
 * @brief The TelegramSingleRquest class Is base class for all single requests commands with arguments.
 *
 * Example:
 * create a single request to telegram server.
 *
 * @code{cpp}
    #include "qTbot/messages/telegramsinglerquest.h"

    class QTBOT_EXPORT TelegramGetMsg final: public TelegramSingleRquest
    {
    public:
        TelegramGetMsg();
    };

    TelegramGetMsg::TelegramGetMsg(int arg1):TelegramSingleRquest("getMe", {{"arg1", arg1}}) {}

 * @endcode
 */
class TelegramSingleRquest: public iRequest
{
public:
    /**
     * @brief TelegramSingleRquest This main constructor of the single requests.
     * @param request This is request name (command)
     * @param args This is list of the request arguments.
     */
    TelegramSingleRquest(const QString &request, const QMap<QString, QVariant> &args);

    /**
     * @brief TelegramSingleRquest This main constructor of the single requests.
     * @param request This is request name (command)
     */
    TelegramSingleRquest(const QString& request);

    QString baseAddress() const override;
    RequestMethod method() const override;

};
}
#endif // TELEGRAMSINGLERQUEST_H
