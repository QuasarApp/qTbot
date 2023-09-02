//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TELEGRAMTEXTMSG_H
#define TELEGRAMTEXTMSG_H

#include <qTbot/itelegrammessage.h>

namespace qTbot {

/**
 * @brief The TelegramTextMsg class This class provide general text mesasges.
 */
class QTBOT_EXPORT TelegramTextMsg: public ITelegramMessage
{
public:
    TelegramTextMsg();

    // ITelegramMessage interface
    void setRawJson(const QJsonObject &newRawJson) override;

    QString text() const;
    void setText(const QString &newText);

private:
    QString _text;
};

}
#endif // TELEGRAMTEXTMSG_H
