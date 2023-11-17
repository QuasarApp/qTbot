//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMMARGS_H
#define TELEGRAMMARGS_H

#include <QVariant>

namespace qTbot {

/**
 * @brief The TelegrammArgs class is base structure for the all tellegram message arguments.
 */
struct TelegrammArgs
{
    TelegrammArgs(const QVariant& id,
                  const QString& text = "",
                  const QString& parseMode = "",
                  unsigned long long replyToMessageId = 0,
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
     * @return
     */
    QMap<QString, QVariant> toMap() const;
};

}
#endif // TELEGRAMMARGS_H
