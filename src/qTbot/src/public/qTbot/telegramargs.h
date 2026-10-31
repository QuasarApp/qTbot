//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMARGS_H
#define TELEGRAMARGS_H

#include <QVariant>
#include "global.h"
#include "irequest.h"

namespace qTbot {

/**
 * @brief The TelegramArgs class is the base structure for all telegram message arguments.
 */
struct QTBOT_EXPORT TelegramArgs
{
    /**
     * @brief TelegramArgs main constructor of the message arguments.
     * @param id This is the id of the target chat or user.
     * @param text This is the text of the message.
     * @param replyToMessageId This is the id of the message to reply to.
     * @param parseMode This is the parse mode of the message.
     * @param disableWebPagePreview Disable web page preview when sending links.
     * @param callBackQueryId This is the callback query id.
     * @param msgIdCB This is the callback function that is invoked with the sent message id.
     * @param priority This is the priority of the request.
     */
    TelegramArgs(const QVariant& id,
                 const QString& text = "",
                 unsigned long long replyToMessageId = 0,
                 const QString& parseMode = "html",
                 bool disableWebPagePreview = false,
                 const QString& callBackQueryId = "",
                 const std::function<void(int msgId)>& msgIdCB = {},
                 iRequest::RequestPriority priority = iRequest::RequestPriority::NormalPriority
                 );

    /**
     * @brief Text of the message.
     * Default: "".
     */
    QString text = "";

    /**
     * @brief Chat ID where the message will be sent.
     * Default: {}.
     */
    QVariant chatId = {};

    /**
     * @brief Callback query ID.
     * Default: "".
     */
    QString callBackQueryId = {};

    /**
     * @brief ID of the message to which a reply will be given.
     * Default: 0.
     */
    unsigned long long replyToMessageId = 0;

    /**
     * @brief Parse mode of the message.
     * Default: "html".
     */
    QString parseMode = "html";

    /**
     * @brief Disable web page preview when sending links.
     * Default: false.
     */
    bool disableWebPagePreview = false;

    /**
     * @brief toMap This method converts all arguments to a map.
     * @param textAsCaption This option forces to replace the text key with the caption key. Used in some requests such as sendDocument.
     * @return list of arguments.
     */
    QMap<QString, QVariant> toMap(bool textAsCaption = false) const;

    /**
     * @brief msgIdCB This is the message id callback function. It will be invoked when the request finishes successfully.
     */
    std::function<void(int msgId)> msgIdCB = {};

    /**
     * @brief requestPriority This is the priority of the request.
     */
    iRequest::RequestPriority requestPriority = iRequest::RequestPriority::NormalPriority;
};

}
#endif // TELEGRAMARGS_H
