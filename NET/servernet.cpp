#include "servernet.hpp"
#include <QRegExp>
Servernet::Servernet(QObject *parent):QTcpServer(parent)
{
    players.clear();
    playernumber=4;
    if(this->listen(QHostAddress::Any,(quint16)28300))
    {
        emit ServerIsRunning();
        qDebug()<<"server okes";
    }
    else {
        emit ServerNetworkError();
        qDebug()<<"server gond";
    }
}
void Servernet::incomingConnection(int socketfd)
{
    QTcpSocket *client=new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);
    players.insert(client, "");

    connect(client,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
}
QStringList Servernet::GetPlayers()
{
    QStringList playerslist;
    playerslist<<name;
    if(players.size()>0)foreach(QString player,players.values())playerslist<<player;
    return playerslist;
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
            players[client]=QString::fromUtf8(message);
            emit NewPlayerConnected();
            QByteArray auth;
            auth.append((uchar)clients.size());     /// ezzel gond van mert
            auth.append((uchar)255);                /// nem 6 bájtként megy át
            auth.append(QByteArray::number(0));     /// a kliens 3 bájtként olvassa
            client->write(auth);
            client->flush();
            sendusernames();
//            if(players.size()==this->playernumber)emit AllPlayersConnected();  /// ettől még fagy
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
    QStringList playerslist=GetPlayers();
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

