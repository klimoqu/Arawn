#pragma once
#include "CORE/command.hpp"
#include <QtNetwork/QtNetwork>

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
signals:
    void CommandReceivedFromClients(Command c);
private slots:
    void readyRead();
    void disconnected();
    void sendusernames();
public slots:
    void SendCommandToClients(Command c);
};
