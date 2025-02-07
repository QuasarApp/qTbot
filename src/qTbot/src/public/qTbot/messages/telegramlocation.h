//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef TELEGRAMLOCATION_H
#define TELEGRAMLOCATION_H

#include <qTbot/ijsonbasedobject.h>

namespace qTbot {

/**
 * @brief The TelegramLocation class just simple struct with latitude and longitude
 */
class QTBOT_EXPORT TelegramLocation: public IJsonBasedObject
{
public:
    TelegramLocation();

    /**
     * @brief Constructs a location object from a JSON object.
     * @param jsonObject The JSON object containing photo data.
     */
    TelegramLocation(const QJsonObject &jsonObject);

    /**
     * @brief latitude is float value of latitude
     * @return float value of latitude
     */
    double latitude() const;

    /**
     * @brief longitude is float value of longitude
     * @return float value of longitude
     */
    double longitude() const;

    /**
     * @brief toQPoint This method convert location data to general qt class.
     * @return location as a qt point
     */
    QPointF toQPoint() const;
};
}
#endif // TELEGRAMLOCATION_H
