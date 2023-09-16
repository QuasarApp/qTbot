//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qvariant.h"
#include <qTbot/telegramrestbot.h>

#include <QCoreApplication>


int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);

    qTbot::TelegramRestBot bot;

    QObject::connect(&bot, &qTbot::TelegramRestBot::sigReceiveMessage, [&bot](auto){
        while(auto msg = bot.takeNextUnreadMessage()) {
            bot.sendSpecificMessage(msg->chatId(), "I see it - я вижу это", msg->messageId());
        }
    });

    bot.login("6349356184:AAFotw9EC46sgAQrkGQ_jeHPyv3EAapZXcM");
    return app.exec();
}
