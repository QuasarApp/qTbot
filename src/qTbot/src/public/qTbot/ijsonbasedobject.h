//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IJSONBASEDOBJECT_H
#define IJSONBASEDOBJECT_H

#include "qjsonobject.h"
#include "global.h"
namespace qTbot {

/**
 * @brief The IJsonBasedObject class This is base interface for all json base objects.
 */
class QTBOT_EXPORT IJsonBasedObject
{
public:
    IJsonBasedObject();
    IJsonBasedObject(const QJsonObject &newRawJson);

    /**
     * @brief rawJson Telegram use rest api with json objects. So all received messages will be parsed in to jsobject.
     * @return js implementation of object.
     */
    const QJsonObject& rawJson() const;

    /**
     * @brief setRawJson this method convert jsobject into telegram message.
     * @param newRawJson new data for telegram message.
     */
    virtual void setRawJson(const QJsonObject &newRawJson);

private:
    QJsonObject _rawJson;
};

}
#endif // IJSONBASEDOBJECT_H
