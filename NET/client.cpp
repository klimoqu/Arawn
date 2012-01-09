#include "client.hpp"

Client::Client(QString address)
{
    tcpSocket = new QTcpSocket(this);
    ds.setDevice(tcpSocket);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReceiveMessageFromServer()));
    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress(address),28300);

}
void Client::SendCommandToServer(Command c)
{
    ds<<c.GetPlayerId()<<c.GetMessageType()<<c.GetMessage();
}
void Client::ReceiveMessageFromServer()
{
    uchar id,type;
    int msg;
    ds>>id>>type>>msg;
    emit CommandReceivedFromServer(Command(id,type,msg));
}
