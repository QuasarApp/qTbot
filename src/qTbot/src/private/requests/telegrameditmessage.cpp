//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegrameditmessage.h"

namespace qTbot {

TelegramEditMessage::TelegramEditMessage(const QVariant &idEditedMessage,
                                         const QVariant& chatId,
                                         const QString& newText,
                                         const QString& parseMode,
                                         bool disableWebPagePreview,
                                         const QString& callBackQueryId,
                                         const QHash<QString, QSharedPointer<QJsonObject> > &extraObjects):
    TelegramSendMsg(chatId,
                    newText,
                    extraObjects,
                    0,
                    parseMode,
                    callBackQueryId,
                    disableWebPagePreview) {


    setRequest("editMessageText");
    addArg("message_id", idEditedMessage);


}
}
