//#
//# Copyright (C) 2023-2026 QuasarApp.
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
    /**
     * @brief IJsonBasedObject default constructor.
     */
    IJsonBasedObject();

    /**
     * @brief IJsonBasedObject constructs the object from a raw json value.
     * @param newRawJson This is the raw json data of the object.
     */
    IJsonBasedObject(const QJsonObject &newRawJson);

    /**
     * @brief rawJson Telegram uses a rest api with json objects. So all received messages are parsed into a json object.
     * @return json implementation of the object.
     */
    const QJsonObject& rawJson() const;

    /**
     * @brief setRawJson This method sets a new raw json data of the object.
     * @param newRawJson This is the new json data of the object.
     */
    virtual void setRawJson(const QJsonObject &newRawJson);

private:
    QJsonObject _rawJson;
};

}
#endif // IJSONBASEDOBJECT_H
