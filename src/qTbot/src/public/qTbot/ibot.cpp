#include "ibot.h"

namespace qTbot {

IBot::IBot()
{

}

QByteArray &IBot::token() const {
    return _token;
}

void IBot::setToken(const QByteArray &newToken) {
    _token = newToken;
}

QString IBot::name() const {
    return _name;
}

void IBot::setName(const QString &newName) {
    _name = newName;
}
}
