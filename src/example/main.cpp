//#
//# Copyright (C) 2021-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "qvariant.h"
#include <qTbot/telegramrestbot.h>

#include <QCoreApplication>
#include <qTbot/httpexception.h>
#include <qTbot/messages/telegrammsg.h>
#include <qTbot/messages/telegramupdate.h>

// link to test bot
// @quasarapp_test_bot (https://t.me/quasarapp_test_bot)
int main(int argc, char *argv[]) {

    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setOrganizationDomain("https://github.com/QuasarApp");
    QCoreApplication::setApplicationName("qTbotExample");

    QCoreApplication app(argc, argv);

    qTbot::TelegramRestBot bot;
    bot.setReqestLimitPerSecond(10);

    srand(time(0));

    QObject::connect(&bot, &qTbot::TelegramRestBot::sigReceiveUpdate, [&bot](auto){
        while(auto&& update = bot.takeNextUnreadUpdate()) {

            if (auto&& tupdate = update.dynamicCast<qTbot::TelegramUpdate>()) {

                if (tupdate->contains(tupdate->MessageUpdate)) {

                    if (auto&& tmsg = tupdate->message()) {
                        if (tmsg->contains(tmsg->Document)) {
                            bot.getFile(tmsg->documents()->fileId(), qTbot::ITelegramBot::Local).then([](const QByteArray& path){
                                                                                                    qInfo() << "file save into " << path;
                                                                                                }).onFailed([](const std::exception& exception){

                                    qCritical() << "exception :" << exception.what();
                                });
                        }

                        if (tmsg->contains(tmsg->Image)) {
                            bot.getFile(tmsg->image()->fileId(), qTbot::ITelegramBot::Local).then([](const QByteArray& path){
                                                                                                qInfo() << "file save into " << path;
                                                                                            }).onFailed([](const std::exception& exception){

                                    qCritical() << "exception :" << exception.what();
                                });;
                        }

                        if (tmsg->contains(tmsg->Audio)) {
                            bot.getFile(tmsg->audio()->fileId(), qTbot::ITelegramBot::Local).then([](const QByteArray& path){
                                                                                                qInfo() << "file save into " << path;
                                                                                            }).onFailed([](const std::exception& exception){

                                    qCritical() << "exception :" << exception.what();
                                });;
                        }

                        if (tmsg->text() == "spam") {
                            for (int i = 0 ; i < 1000; i++) {
                                bot.sendMessage(tmsg->chatId(), QString(" message N %0").arg(i), qTbot::iRequest::LowPriority);
                            }
                        } else {
                            bot.sendSpecificMessageWithKeyboard(qTbot::TelegramArgs{tmsg->chatId(), "I see it", tmsg->messageId()},
                                                                {{{"test_button", [tmsg, &bot](const QString& queryId, const QVariant& msgId){
                                                                       static int index = 0;

                                                                       auto&& args = qTbot::TelegramArgs{tmsg->chatId(),
                                                                                                         "I see it. Presed count: " + QString::number(index++),
                                                                                                         tmsg->messageId(),
                                                                                                         "",
                                                                                                         false,
                                                                                                         queryId};

                                                                       auto&& keyboard = qTbot::KeyboardOnMessage{
                                                                                                                  {{"test_button", [](auto , auto ){}},
                                                                                                                   {"test_button 2", [](auto , auto ){}}}};

                                                                       bot.editSpecificMessageWithKeyboard(msgId,
                                                                                                           args,
                                                                                                           keyboard
                                                                                                           );
                                                                   }}}});

                            bot.sendSpecificMessageWithKeyboard(qTbot::TelegramArgs{tmsg->chatId(), "I see it", tmsg->messageId()},
                                                                {{{"test_button"},
                                                                    {"test_button"},}}, true, true);
                        }


                    }

                }
            }
        }
    });

    if (!bot.login("6349356184:AAFotw9EC46sgAQrkGQ_jeHPyv3EAapZXcM")) {
        qCritical() << "failed to login!";
        return 1;
    }
    return app.exec();
}
