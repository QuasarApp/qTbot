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
#include <qTbot/messages/telegramupdate.h>

int main(int argc, char *argv[]) {

    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setOrganizationDomain("https://github.com/QuasarApp");
    QCoreApplication::setApplicationName("qTbotExample");

    QCoreApplication app(argc, argv);

    qTbot::TelegramRestBot bot;

    srand(time(0));

    QList<QSharedPointer<qTbot::iFile> > filesStack;
    QObject::connect(&bot, &qTbot::TelegramRestBot::sigReceiveUpdate, [&bot, &filesStack](auto){
        while(auto&& update = bot.takeNextUnreadUpdate()) {

            if (auto&& tupdate = update.dynamicCast<qTbot::TelegramUpdate>()) {

                if (tupdate->contains(tupdate->MessageUpdate)) {

                    if (auto&& tmsg = tupdate->message()) {
                        if (tmsg->contains(tmsg->Document)) {
                            filesStack.push_back(bot.getFile(tmsg->documents()->fileId(), qTbot::iFile::Local));
                        }

                        if (tmsg->contains(tmsg->Image)) {
                            filesStack.push_back(bot.getFile(tmsg->image()->fileId(), qTbot::iFile::Local));
                        }

                        if (tmsg->contains(tmsg->Audio)) {
                            filesStack.push_back(bot.getFile(tmsg->audio()->fileId(), qTbot::iFile::Local));
                        }
                        bot.sendSpecificMessageWithKeyboard(tmsg->chatId(), "I see it - я вижу это", {{{"test_button", [tmsg, &bot](const QString& queryId){
                                                                                               bot.sendSpecificMessage(tmsg->chatId(), "stop to presse a button",{}, queryId);
                                                                                                        }}}}, {}, false, false, tmsg->messageId());
                    }

                }
            }
        }
    });

    bot.login("6349356184:AAFotw9EC46sgAQrkGQ_jeHPyv3EAapZXcM");
    return app.exec();
}
