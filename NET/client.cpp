#include "client.hpp"

Client::Client(QString address)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->connectToHost(address,28300);
}
void Client::readyRead()
{
    QByteArray message=socket->readAll();
        if(message.count()==6)
        {
            uchar id=message.at(0);
            uchar type=message.at(1);
            int msg=message.right(4).toInt();
            emit CommandReceivedFromServer(Command(id,type,msg));
        }
        else
        {
            players = QString(message).split(",");
        }
}
void Client::SendCommandToServer(Command c)
{
    QByteArray command;
    command.append((uchar)c.GetPlayerId());
    command.append((uchar)c.GetMessageType());
    command.append(QByteArray::number(c.GetMessage()));
    socket->write(command);
    socket->flush();
}
