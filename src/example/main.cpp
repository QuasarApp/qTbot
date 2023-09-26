//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qvariant.h"
#include <qTbot/telegramrestbot.h>

#include <QCoreApplication>
#include <qTbot/messages/telegrammsg.h>

int main(int argc, char *argv[]) {

    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setOrganizationDomain("https://github.com/QuasarApp");
    QCoreApplication::setApplicationName("qTbotExample");

    QCoreApplication app(argc, argv);

    qTbot::TelegramRestBot bot;

    QList<QSharedPointer<qTbot::iFile> > filesStack;
    QObject::connect(&bot, &qTbot::TelegramRestBot::sigReceiveMessage, [&bot, &filesStack](auto){
        while(auto&& msg = bot.takeNextUnreadMessage()) {

            if (auto&& tmsg = msg.dynamicCast<qTbot::TelegramMsg>()) {

                if (tmsg->contains(tmsg->Document)) {
                    filesStack.push_back(bot.getFile(tmsg->documents()->fileId(), qTbot::iFile::Local));
                }

                if (tmsg->contains(tmsg->Image)) {
                    filesStack.push_back(bot.getFile(tmsg->image()->fileId(), qTbot::iFile::Local));
                }

                if (tmsg->contains(tmsg->Audio)) {
                    filesStack.push_back(bot.getFile(tmsg->audio()->fileId(), qTbot::iFile::Local));
                }

                bot.sendSpecificMessage(tmsg->chatId(), "I see it - я вижу это", tmsg->messageId());

            }
        }
    });

    bot.login("6349356184:AAFotw9EC46sgAQrkGQ_jeHPyv3EAapZXcM");
    return app.exec();
}
