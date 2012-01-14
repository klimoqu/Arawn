#include "client.hpp"

Client::Client(QString name)
{
    this->name=name;
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SIGNAL(Connected()));
    connect(socket, SIGNAL(connected()), this, SLOT(SendUsernameToServer()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(ConnectionFailed()));
}

void Client::connectToServer(QString address)
{
    socket->connectToHost(address,(quint16)28300);
    socket->waitForConnected();
}

void Client::readyRead()
{
    QByteArray message=socket->readAll();
    qDebug() << "meret: " << message.count();
        if(message.count()==6)
        {
            uchar id=message.at(0);
            uchar type=message.at(1);
            int msg=message.right(4).toInt();
            emit CommandReceivedFromServer(Command(id,type,msg));
        }
        else
        {
            qDebug() << message;
            players = QString(message).split(",");
            emit refreshPlayers();
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
void Client::SendUsernameToServer()
{
    socket->write(name.toUtf8());
    socket->flush();
}
