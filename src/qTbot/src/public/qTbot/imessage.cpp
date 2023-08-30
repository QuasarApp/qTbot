#include "imessage.h"

iMessage::iMessage() {

}

const QByteArray& iMessage::rawData() const {
    return _rawData;
}

void iMessage::setRawData(const QByteArray &newRawData) {
    _rawData = newRawData;
}

const QByteArray &iMessage::userId() const {
    return _userId;
}

void iMessage::setUserId(const QByteArray &newUserId) {
    _userId = newUserId;
}
