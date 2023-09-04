//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#



#ifndef ITELEGRAMBOT_H
#define ITELEGRAMBOT_H

#include "ibot.h"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

namespace qTbot {

class ITelegramMessage;

/**
 * @brief The ITelegramBot class This is base implementation of the all telegramm bots.
 */
class QTBOT_EXPORT ITelegramBot : public QObject, public IBot
{
    Q_OBJECT
public:
    ITelegramBot();
    ~ITelegramBot();

    bool login(const QByteArray &token) override;
    bool sendMessage(const QSharedPointer<iMessage> &message) override;

    /**
     * @brief id This method return bots id number.
      * @return bots id number.
     */
    unsigned long long id() const;

    /**
     * @brief name This is name of the bot.
     * @return name of the bot.
     */
    QString name() const;

    /**
     * @brief username This is bots login
     * @return bots login.
     */
    QString username() const;

protected:
    /**
     * @brief setId This method sets new value for the ITelegramBot::id property.
     * @param newId this is new value of the ITelegramBot::id property.
     */
    void setId(unsigned long long newId);

    /**
     * @brief setName This method sets new value for the ITelegramBot::name property.
     * @param newName this is new value of the ITelegramBot::name property.
     */
    void setName(const QString &newName);

    /**
     * @brief setUsername This method sets new value for the ITelegramBot::username property.
     * @param newUsername this is new value of the ITelegramBot::username property.
     */
    void setUsername(const QString &newUsername);

    /**
     * @brief makePrefix This method prepare a prefix message for all telegramm bots.
     * @return telegramm request prefix/
     */
    QByteArray makePrefix() const;

    /**
     * @brief onMessageReceived This method will be invoked every time when network rplays will be finished.
     * @param replay This is ansver of the server.
     */
    virtual void onMessageReceived(const QSharedPointer<ITelegramMessage>& replay);;

private slots:
    void handleReplayIsFinished();

signals:
    void receiveMessage(const QSharedPointer<iMessage>&  );

private:
    unsigned long long _id = 0;
    QString _name;
    QString _username;

    QNetworkAccessManager *_manager = nullptr;

};
}
#endif // ITELEGRAMBOT_H
