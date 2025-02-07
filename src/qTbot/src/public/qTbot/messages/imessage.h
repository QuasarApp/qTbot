//#
//# Copyright (C) 2023-2025 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IMESSAGE_H
#define IMESSAGE_H

#include "qTbot/ijsonbasedupdate.h"
namespace qTbot {

/**
 * @brief The iMessage class This is main interface for the all messages.
 */
class QTBOT_EXPORT iMessage: public IJsonBasedUpdate
{
public:
    iMessage();

    /**
     * @brief updateId This method returns numeric id of the message.
     * @return numeric id of the message.
     */
    virtual unsigned long long messageId() const = 0;
};
}
#endif // IMESSAGE_H
