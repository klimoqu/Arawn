#pragma once
#include "../CORE/command.hpp"
#include <QtNetwork>

class Client:public QObject
{
    Q_OBJECT
    QTcpSocket *socket;
    uchar playerid;
    QStringList players;
    QString name;
public:
    Client(QString name);
    uchar GetPlayerID()const{return playerid;}
    QStringList GetPlayers()const {return players;}
signals:
    void Connected();
    void ConnectionFailed();
    void refreshPlayers();
    void CommandReceivedFromServer(Command c);
	void Disconnected();
private slots:
    void readyRead();
public slots:
    void SendCommandToServer(Command c);
    void SendUsernameToServer();
    void connectToServer(QString address);
};

