#include "Server.h"
#include <stdlib.h>
#include <QtNetwork>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    c = new Command(2,4,6);
    list = new QList<connection*>();
    sendThread = new SenderThread(list, this);
    connect(this, SIGNAL(SendMessage(Command*)), sendThread, SLOT(SenderThreadMessage(Command*)));
    connect(this, SIGNAL(finish()), sendThread, SLOT(clearMessage()));
    connect(this, SIGNAL(newConnection()), this, SIGNAL(NewClientConnected()));
    connect(sendThread, SIGNAL(debugsSenderThread(QString)), SIGNAL(debugs(QString)));


    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAdress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAdress.isEmpty())
        ipAdress = QHostAddress(QHostAddress::LocalHost).toString();

    this->port = 28300;
    QHostAddress ip(ipAdress);
    listen(ip, this->port);
}

Server::~Server()
{
    emit finish();
    for(int i=0;i<list->size();i++)
    {
        list->at(i)->disconnect();
    }
}

void Server::incomingConnection(int socketDescriptor)
{
    connection *uj = new connection();
    uj->setSocketDescriptor(socketDescriptor);

    connect(uj, SIGNAL(disconnected()), this, SLOT(remove()));

    list->push_front(uj);
    ListenThread *hallgato = new ListenThread(this, uj);

    connect(hallgato, SIGNAL(debugsListenThread(QString)), SIGNAL(debugs(QString)));
    connect(hallgato, SIGNAL(ListenThreadMessage(Command*)), this, SIGNAL(ServerNewMessage(Command*)));
    connect(uj, SIGNAL(readyRead()), hallgato, SLOT(start()));
    hallgato->start();
}

bool Server::isServer()
{
    return true;
}

void Server::ServerSendMessage(Command *str)
{
    if(!sendThread->isRunning()){
            sendThread = new SenderThread(list, this);
            sendThread->SenderThreadMessage(str);
            sendThread->start();
    }
    else emit SendMessage(str);
}

void Server::remove()
{
    for(int i=list->size()-1;i>=0;i--)
    {
        if(!list->at(i)->isOpen()) list->removeAt(i);
    }
}

QString Server::getIpAdress(){return ipAdress;}
qint32 Server::getPort(){return port;}
