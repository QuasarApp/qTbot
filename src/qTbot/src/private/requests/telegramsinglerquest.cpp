//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "telegramsinglerquest.h"
#include "qvariant.h"

#include <QString>


namespace qTbot {

TelegramSingleRquest::TelegramSingleRquest(const QString& request,
                                           const QMap<QString, QVariant>& args) {
    setRequest(request);
    setArgs(args);}

TelegramSingleRquest::TelegramSingleRquest(const QString &request) {
    setRequest(request);
}
\
QString TelegramSingleRquest::baseAddress() const {
    return "https://api.telegram.org";
}

}
