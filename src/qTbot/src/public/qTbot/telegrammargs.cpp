//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "telegrammargs.h"
namespace qTbot {

TelegrammArgs::TelegrammArgs(const QVariant &id,
                             const QString &text,
                             const QString &parseMode,
                             unsigned long long replyToMessageId,
                             bool disableWebPagePreview,
                             const QString &callBackQueryId)
{

    this->chatId = id;
    this->text = text;
    this->callBackQueryId = callBackQueryId;
    this->disableWebPagePreview = disableWebPagePreview;
    this->replyToMessageId = replyToMessageId;
    this->parseMode = parseMode;
}

QMap<QString, QVariant> TelegrammArgs::toMap() const {
    QMap<QString, QVariant> args {{"chat_id", chatId}};

    if (text.size()) {
        args["text"] = text;
    }

    if (replyToMessageId) {
        args["reply_to_message_id"] = replyToMessageId;
    }

    if (parseMode.size()) {
        args["parse_mode"] = parseMode;
    }

    if (disableWebPagePreview) {
        args["disable_web_page_preview"] = disableWebPagePreview;
    }

    if (callBackQueryId.size()) {
        args["callback_query_id"] = callBackQueryId;
    }

    return args;
}

}
