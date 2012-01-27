#pragma once
#include "../CORE/command.hpp"
#include <QtNetwork>

class Servernet:public QTcpServer
{
    Q_OBJECT
    uchar playernumber,actid;
    QSet<QTcpSocket*> clients;
    QMap<QTcpSocket*,QString> players;
    QString name;
	bool survive;
protected:
    void incomingConnection(int socketfd);
public:
    Servernet(QObject *parent=0);
    void SetLocalPlayername(QString name){this->name=name;}
    void SetPlayerNumber(uchar num){playernumber=num-1;}
    uchar GetPlayerNumber()const{return playernumber;}
    QStringList GetPlayers();
	void SetSurviveCup(bool survive){this->survive=survive;}
signals:
    void CommandReceivedFromClients(Command c);
    void ServerIsRunning();
    void ServerNetworkError();
    void NewPlayerConnected();
    void AllPlayersConnected();
	void PlayerDisconnected();
private slots:
    void readyRead();
    void disconnected();
    void sendusernames();
public slots:
    void SendCommandToClients(Command c);

};
