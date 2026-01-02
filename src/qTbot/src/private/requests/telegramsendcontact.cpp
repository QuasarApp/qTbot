//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramsendcontact.h"

namespace qTbot {


TelegramSendContact::TelegramSendContact(const TelegramArgs &args,
                                         const QString &firstName,
                                         const QString &phone,
                                         const QString &lastName):
    TelegramSingleRquest("sendContact", args.toMap(true)) {

    addArg("first_name", firstName);
    addArg("last_name", lastName);
    addArg("phone_number", phone);
    setPriority(args.requestPriority);


}

}
