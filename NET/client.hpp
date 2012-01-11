#pragma once
#include "CORE/command.hpp"
#include <QtNetwork/QtNetwork>
/*

Tesztelésre vár, ne nyúlj hozzá

*/
class Client:public QObject
{
    Q_OBJECT
    QTcpSocket *socket;
    uchar playerid;
    QStringList players;
public:
    Client(QString address);
    uchar GetPlayerID(){return playerid;}
signals:
    void Connected();
    void ConnectionFailed();
    void CommandReceivedFromServer(Command c);
private slots:
    void readyRead();
public slots:
    void SendCommandToServer(Command c);
};
