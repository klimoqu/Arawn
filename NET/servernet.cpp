#include "NET/servernet.hpp"
#include <QRegExp>
Servernet::Servernet(QObject *parent):QTcpServer(parent)
{
    playernumber=4;
    this->listen(QHostAddress::Any,28300);
}
void Servernet::incommingConnection(int socketfd)
{
    QTcpSocket *client=new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);
    connect(client,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
}
void Servernet::readyRead()
{
    QTcpSocket *client =(QTcpSocket*)sender();
    QByteArray message=client->readAll();
        if(message.count()==6)
        {
            uchar id=message.at(0);
            uchar type=message.at(1);
            int msg=message.right(4).toInt();
            emit CommandReceivedFromClients(Command(id,type,msg));
        }
        else
        {
            players[client]=QString(message);
            QByteArray auth;
            auth.append((uchar)clients.size());
            auth.append((uchar)255);
            auth.append(QByteArray::number(0));
            client->write(auth);
            client->flush();
            sendusernames();
        }
}
void Servernet::disconnected()
{
    QTcpSocket *client =(QTcpSocket*)sender();
    clients.remove(client);
    QString user=players[client];
    players.remove(client);
    sendusernames();
}
void Servernet::sendusernames()
{
    QStringList playerslist;
    foreach(QString player,players.values())playerslist<<player;
    foreach(QTcpSocket *client,clients)client->write(QString(playerslist.join(",")).toUtf8());
}
void Servernet::SendCommandToClients(Command c)
{
    QByteArray command;
    command.append((uchar)c.GetPlayerId());
    command.append((uchar)c.GetMessageType());
    command.append(QByteArray::number(c.GetMessage()));
    foreach(QTcpSocket *client,clients){client->write(command);client->flush();}
}
