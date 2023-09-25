//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IREQUEST_H
#define IREQUEST_H

#include "qTbot/global.h"

namespace qTbot {

/**
 * @brief The iRequest class Is main interface for all custom requests.
 * @see IBot::sendRequest
 */
class QTBOT_EXPORT iRequest
{
public:
    iRequest();

    /**
     * @brief makeUpload This method prepare data to upload;
     * @return data array prepared to sending.
     */
    virtual QString makeUpload() const = 0;

    /**
     * @brief baseAddress This method return base domain of remote server.
     * @return base domain name of remoute server.
     */
    virtual QString baseAddress() const = 0;
};

}
#endif // IREQUEST_H
