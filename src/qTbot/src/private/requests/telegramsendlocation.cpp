//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramsendlocation.h"

#include <QJsonDocument>
namespace qTbot {

TelegramSendLocation::TelegramSendLocation(const TelegramArgs &args,
                                           float latitude,
                                           float longitude,
                                           const ExtraJsonObjects &extraObjects):
    TelegramSingleRquest("sendLocation", args.toMap(true)) {

    addArg("latitude", latitude);
    addArg("longitude", longitude);
    setPriority(args.requestPriority);


    for (auto it = extraObjects.begin(); it != extraObjects.end(); it = std::next(it)) {
        addArg(it.key(), QJsonDocument(*it.value()).toJson(QJsonDocument::Compact));
    }
}

}
