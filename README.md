# qTbot 
This is Qt library for working with chat bots. 

At this time This library supports next platforms:
* Telegram (50%) - implemented only processing and sending messages and download files.

## Build and Include
* cd yourRepo
* git submodule add https://github.com/QuasarApp/easyssl.git # add the repository of Heart into your repo like submodule
* git submodule update --init --recursive
* Include in your CMakeLists.txt file the main CMakeLists.txt file of Heart library

    ```cmake
    add_subdirectory(easyssl)
    ```
    
* link the Heart library to your target
    ```cmake
    target_link_libraries(yourLib PUBLIC easyssl)
    ```
* rebuild yuor project


## Using

``` cpp

#include <qTbot/telegramrestbot.h>
#include <qTbot/messages/telegrammsg.h>
#include <qTbot/messages/telegramupdate.h>

int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);

    qTbot::TelegramRestBot bot;

    QObject::connect(&bot, &qTbot::TelegramRestBot::sigReceiveUpdate, [&bot, &filesStack](auto){
        while(auto&& update = bot.takeNextUnreadUpdate()) {

            if (auto&& tupdate = update.dynamicCast<qTbot::TelegramUpdate>()) {

                if (tupdate->contains(tupdate->MessageUpdate)) {

                    if (auto&& tmsg = tupdate->message()) {
                        if (tmsg->contains(tmsg->Document)) {
                            bot.getFile(tmsg->documents()->fileId(), qTbot::iFile::Local);
                        }

                        if (tmsg->contains(tmsg->Image)) {
                            bot.getFile(tmsg->image()->fileId(), qTbot::iFile::Local);
                        }

                        if (tmsg->contains(tmsg->Audio)) {
                            bot.getFile(tmsg->audio()->fileId(), qTbot::iFile::Local);
                        }
                        bot.sendSpecificMessage(tmsg->chatId(), "I see it - я вижу это", tmsg->messageId());
                    }

                }
            }
        }
    });

    bot.login("6349356184:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    
    return app.exec();
}

```
