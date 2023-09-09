//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMSINGLERQUEST_H
#define TELEGRAMSINGLERQUEST_H

#include <qTbot/itelegrammessage.h>

namespace qTbot {

/**
 * @brief The TelegramSingleRquest class Is base class for all single requests commands.
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

    TelegramGetMsg::TelegramGetMsg():TelegramSingleRquest("getMe") {}

 * @endcode
 */
class QTBOT_EXPORT TelegramSingleRquest: public iRequest
{
public:
    /**
     * @brief TelegramSingleRquest This main constructor of the single requests.
     * @param request This is request name (command)
     * @param args This is list of the request arguments.
     */
    TelegramSingleRquest(QByteArray&& request, QMap<QString, QVariant>&& args);
    QByteArray makeUpload() const override final;

private:
    QByteArray _request;
    QMap<QString, QVariant> _args;

};
}
#endif // TELEGRAMSINGLERQUEST_H
