#pragma once
#include "../CORE/command.hpp"
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
    QString name;
public:
    Client(QString name);
    uchar GetPlayerID(){return playerid;}
    QStringList GetPlayers(){return players;}
signals:
    void Connected();
    void ConnectionFailed();
    void refreshPlayers();
    void CommandReceivedFromServer(Command c);
private slots:
    void readyRead();
public slots:
    void SendCommandToServer(Command c);
    void SendUsernameToServer();
    void connectToServer(QString address);
};

