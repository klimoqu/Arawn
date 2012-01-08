#pragma once
#include "NET/sockethandler.hpp"

class Servernet:public QObject
{
    Q_OBJECT
    uchar playersnumber,act;
    QTcpServer *tcpServer;
    Sockethandler *clientConnections[3];

public:
    Servernet(uchar playersnumber);
signals:
    void CommandReceivedFromClients(Command c);
    void CommandReceivedFromServer(Command c);
private slots:
    void getConnection();
public slots:
    void GetMessageFromClients(Command c){emit CommandReceivedFromClients(c);}
    void SendCommandToClients(Command c){emit CommandReceivedFromServer(c);}
};
