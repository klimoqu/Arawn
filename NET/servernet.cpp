#include "NET/servernet.hpp"
Servernet::Servernet(uchar playersnumber)
{
    this->playersnumber=playersnumber;
    this->tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any,23800)) {}
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(getConnection()));
    act=0;
}

void Servernet::getConnection()
{
    if(act==playersnumber)return;
    clientConnections[act] = new Sockethandler(tcpServer->nextPendingConnection());
    connect(clientConnections[act],SIGNAL(MessageReceived(Command)),this,SLOT(GetMessageFromClients(Command)));
    connect(this,SIGNAL(CommandReceivedFromServer(Command)),clientConnections[act],SLOT(SendMessage(Command)));
    act++;
}
