//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef ITELEGRAMBOT_H
#define ITELEGRAMBOT_H

#include "qTbot/global.h"
#include "qTbot/imessage.h"

#include <QSharedPointer>
namespace qTbot {

struct TelegramMessage
{

};

class QTBOT_EXPORT iTelegramBot
{
public:
    iTelegramBot();

    virtual const QString& name() const;
    virtual const QByteArray& token() const;

signals:
};
}
#endif // ITELEGRAMBOT_H
