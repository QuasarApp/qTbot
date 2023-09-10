//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IJSONBASEDMESSAGE_H
#define IJSONBASEDMESSAGE_H

#include "imessage.h"
#include "qTbot/ijsonbasedobject.h"

#include <QJsonObject>

namespace qTbot {

/**
 * @brief The IJsonBasedMessage class This is message that have a json sructure
 */
class QTBOT_EXPORT IJsonBasedMessage: public iMessage, public IJsonBasedObject
{
public:
    IJsonBasedMessage();

    // iMessage interface
    bool isValid() const override;
    void setRawData(const QByteArray &newRawData) override;
};
}
#endif // IJSONBASEDMESSAGE_H
