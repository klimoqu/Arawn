#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include "connection.h"
#include "SenderThread.h"
#include "ListenThread.h"
#include "abstractNET.h"
#include "QObject"

class Server : public QTcpServer, public abstractNet
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    virtual ~Server();
    bool isServer();
    QString getIpAdress();
    qint32 getPort();

signals:
    void SendMessage(Command *str);
    void ServerNewMessage(Command *str);
    void NewClientConnected();
    void finish();
    void debugs(QString);

public slots:
    void ServerSendMessage(Command *str);
    void remove();

protected:
    void incomingConnection(int socketDescriptor);

private:
    SenderThread *sendThread;
    QList<connection*> *list;
    Command *c;
    QString ipAdress;
    qint32 port;
};

#endif
