#include "telegraminlinekeyboardcallback.h"

namespace qTbot {

TelegramInlineKeyBoardCallBack::TelegramInlineKeyBoardCallBack()
{

}

TelegramInlineKeyBoardCallBack::TelegramInlineKeyBoardCallBack(const QJsonObject &jsonObject):
    IJsonBasedObject(jsonObject)  {

}

unsigned long long TelegramInlineKeyBoardCallBack::fromId() const {
    return rawJson()["from"]["id"].toInteger();
}

bool TelegramInlineKeyBoardCallBack::isBot() const {
    return rawJson()["from"]["is_bot"].toBool();
}

QString TelegramInlineKeyBoardCallBack::firstName() const {
    return rawJson()["from"]["first_name"].toString();
}

QString TelegramInlineKeyBoardCallBack::lastName() const {
    return rawJson()["from"]["last_name"].toString();
}

QString TelegramInlineKeyBoardCallBack::username() const {
    return rawJson()["from"]["username"].toString();
}

QString TelegramInlineKeyBoardCallBack::languageCode() const {
    return rawJson()["from"]["language_code"].toString();
}

QString TelegramInlineKeyBoardCallBack::callBackData() const {
    return rawJson()["data"].toString();
}

QVariant TelegramInlineKeyBoardCallBack::messageId() const {
    return rawJson()["message"]["message_id"].toVariant();
}
}
