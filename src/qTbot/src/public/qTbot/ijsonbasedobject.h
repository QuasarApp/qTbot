//#
//# Copyright (C) 2023-2023 QuasarApp.
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

    /**
     * @brief IJsonBasedObject This constructor sets source sjon object for this wrapper object.
     * @param newRawJson This is new source of object.
     */
    IJsonBasedObject(const QJsonObject &newRawJson);

    /**
     * @brief IJsonBasedObject This constructor sets a source and specific address to object. Use this constructor if the source object is array;
     * @param newRawJson This is new source of object.
     * @param arrayAddress This is specific address to the object.
     */
    IJsonBasedObject(const QJsonObject &newRawJson, const QList<QVariant>& arrayAddress);

    /**
     * @brief rawJson Telegram use rest api with json objects. So all received messages will be parsed in to jsobject.
     * @return js implementation of object.
     */
    const QSharedPointer<const QJsonObject>& rawJson() const;

    /**
     * @brief setRawJson this method convert jsobject into telegram message.
     * @param newRawJson new data for telegram message.
     */
    virtual void setRawJson(const QJsonObject &newRawJson);

    /**
     * @brief arrayAddress This method contains address to the specific object of all json object;
     * @return specific address to json object.
     */
    const QList<QVariant>& arrayAddress() const;

protected:
    /**
     * @brief setArrayAddress Sets new specific address for the current json object.
     * @param newArrayAddress new address of specific object.
     * @see IJsonBasedObject::addressRef
     */
    void setArrayAddress(const QList<QVariant> &newArrayAddress);

    /**
     * @brief addressRef returns current specific object by saved ref
     * @return current specific object by saved ref
     * @see IJsonBasedObject::setArrayAddress
     * @see IJsonBasedObject::arrayAddress
     */
    QJsonValue addressRef() const;

private:
    QSharedPointer<const QJsonObject> _rawJson;
    QList<QVariant> _arrayAddress;
};

}
#endif // IJSONBASEDOBJECT_H
