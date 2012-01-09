#include "NET/sockethandler.hpp"
#include <iostream>
Sockethandler::Sockethandler(QTcpSocket *socket,uchar id)
{
    this->clientSocket=socket;
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(receivemessage()));
    connect(clientSocket, SIGNAL(disconnected()),clientSocket, SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(disconnected()),this, SLOT(killMe()));
    QDataStream ds(clientSocket);
    ds<<id<<255<<0;
}

void Sockethandler::receivemessage()
{
    QDataStream ds(clientSocket);
    uchar id,type;
    int msg;
    ds>>id>>type>>msg;
    emit MessageReceived(Command(id,type,msg));
}
void Sockethandler::killme()
{
    if(this!=0)delete this;
}
void Sockethandler::SendMessage(Command c)
{
    QDataStream ds(clientSocket);
    ds<<c.GetPlayerId()<<c.GetMessageType()<<c.GetMessage();
}
