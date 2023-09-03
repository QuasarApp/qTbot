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

protected:
    /**
     * @brief makePrefix This method prepare a prefix message for all telegramm bots.
     * @return telegramm request prefix/
     */
    QByteArray makePrefix() const;

    /**
     * @brief onMessageReceived This method will be invoked every time when network rplays will be finished.
     * @param replay This is ansver of the server.
     */
    virtual void onMessageReceived(const QSharedPointer<ITelegramMessage>& replay) = 0;

private slots:
    void handleReplayIsFinished();

signals:
    void receiveMessage(const QSharedPointer<iMessage>&  );

private:
    QNetworkAccessManager *_manager = nullptr;

};
}
#endif // ITELEGRAMBOT_H
