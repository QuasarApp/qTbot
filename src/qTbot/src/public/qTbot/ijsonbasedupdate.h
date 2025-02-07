//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IJSONBASEDUPDATE_H
#define IJSONBASEDUPDATE_H

#include "iupdate.h"
#include "qTbot/ijsonbasedobject.h"

#include <QJsonObject>

namespace qTbot {

/**
 * @brief The IJsonBasedUpdate class This is updates that have a json sructure
 */
class QTBOT_EXPORT IJsonBasedUpdate: public iUpdate, public IJsonBasedObject
{
public:
    IJsonBasedUpdate();

    // iMessage interface
    bool isValid() const override;
    void setRawData(const QByteArray &newRawData) override;
};
}
#endif // IJSONBASEDUPDATE_H
