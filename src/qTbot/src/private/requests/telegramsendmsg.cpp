//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegramsendmsg.h"

#include <QJsonDocument>
#include <QJsonObject>
namespace qTbot {

TelegramSendMsg::TelegramSendMsg(const QVariant &chatId,
                                 const QString &text,
                                 const QMap<QString, QJsonObject> &extraObjects,
                                 unsigned long long replyToMessageId,
                                 bool markdown,
                                 bool disableWebPagePreview)
                                 :
    TelegramSingleRquest("sendMessage")
{

    QMap<QString, QVariant> args {{"chat_id", chatId}, {"text", text}};

    if (replyToMessageId) {
        args["reply_to_message_id"] = replyToMessageId;
    }

    if (markdown) {
        args["parse_mode"] = "Markdown";
    }

    if (disableWebPagePreview) {
        args["disable_web_page_preview"] = disableWebPagePreview;
    }

    for (auto it = extraObjects.begin(); it != extraObjects.end(); it = std::next(it)) {
        args[it.key()] = QJsonDocument(it.value()).toJson();
    }

    setArgs(args);
}
}
