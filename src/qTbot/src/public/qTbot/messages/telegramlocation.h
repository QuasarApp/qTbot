//#
//# Copyright (C) 2023-2026 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMLOCATION_H
#define TELEGRAMLOCATION_H

#include <qTbot/ijsonbasedobject.h>

namespace qTbot {

/**
 * @brief The TelegramLocation class is a simple struct with latitude and longitude.
 */
class QTBOT_EXPORT TelegramLocation: public IJsonBasedObject
{
public:
    /**
     * @brief TelegramLocation default constructor.
     */
    TelegramLocation();

    /**
     * @brief Constructs a location object from a JSON object.
     * @param jsonObject The JSON object containing location data.
     */
    TelegramLocation(const QJsonObject &jsonObject);

    /**
     * @brief latitude This is the float value of the latitude.
     * @return float value of the latitude
     */
    double latitude() const;

    /**
     * @brief longitude This is the float value of the longitude.
     * @return float value of the longitude
     */
    double longitude() const;

    /**
     * @brief toQPoint This method converts the location data to the general qt class.
     * @return location as a qt point
     */
    QPointF toQPoint() const;
};
}
#endif // TELEGRAMLOCATION_H
