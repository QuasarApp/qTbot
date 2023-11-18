//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMARGS_H
#define TELEGRAMARGS_H

#include <QVariant>

namespace qTbot {

/**
 * @brief The TelegramArgs class is base structure for the all tellegram message arguments.
 */
struct TelegramArgs
{
    TelegramArgs(const QVariant& id,
                 const QString& text = "",
                 unsigned long long replyToMessageId = 0,
                 const QString& parseMode = "html",
                 bool disableWebPagePreview = false,
                 const QString& callBackQueryId = ""
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
     * @brief toMap convert all arguments to the map.
     * @param textAsCaption This option force to replace text key to caption. Used on some requests as a sendDocument
     * @return list of arguments.
     */
    QMap<QString, QVariant> toMap(bool textAsCaption = false) const;
};

}
#endif // TELEGRAMARGS_H
