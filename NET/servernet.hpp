#pragma once
#include "CORE/command.hpp"
#include <QtNetwork/QtNetwork>
/*

Tesztelésre vár, ne nyúlj hozzá

*/
class Servernet:public QTcpServer
{
    Q_OBJECT
    uchar playernumber,actid;
    QSet<QTcpSocket*> clients;
    QMap<QTcpSocket*,QString> players;
protected:
    void incommingConnection(int socketfd);
public:
    Servernet(QObject *parent=0);
    void SetPlayerNumber(uchar num){playernumber=num;}
    uchar GetPlayerNumber(){return playernumber;}
    QStringList GetPlayers();
signals:
    void CommandReceivedFromClients(Command c);
    void ServerIsRunning();
    void ServerNetworkError();
    void NewPlayerConnected(QString newplayername);
private slots:
    void readyRead();
    void disconnected();
    void sendusernames();
public slots:
    void SendCommandToClients(Command c);
};
