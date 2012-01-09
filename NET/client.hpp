#pragma once
#include "NET/sockethandler.hpp"

class Client:public QObject
{
    Q_OBJECT
    QTcpSocket *tcpSocket;
    QDataStream ds;
public:
    Client(QString address);
signals:
    void CommandReceivedFromServer(Command c);
private slots:
    void ReceiveMessageFromServer();
public slots:
    void SendCommandToServer(Command c);
};
