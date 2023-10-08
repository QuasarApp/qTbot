//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMEDITMESSAGE_H
#define TELEGRAMEDITMESSAGE_H

#include "telegramsendmsg.h"
namespace qTbot {

/**
 * @brief The TelegramEditMessage class This command edit keyboard of the message.
 */
class TelegramEditMessage: public TelegramSendMsg
{
public:
    TelegramEditMessage(const QVariant& idEditedMessage,
                       const QVariant& chatId,
                       const QString& newText,
                       bool markdown = true,
                       bool disableWebPagePreview = false,
                       const QString& callBackQueryId = "",
                       const QMap<QString, QSharedPointer<QJsonObject>>& extraObjects = {});
};
}
#endif // TELEGRAMEDITMESSAGE_H
