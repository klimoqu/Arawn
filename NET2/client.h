#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include "clientthread.h"
#include "connection.h"
#include "command.hpp"
#include "abstractNET.h"

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE

class Client : public QObject, public abstractNet
{
    Q_OBJECT

public:
    Client(QObject *parent = 0);
    ~Client();
    bool isServer();

signals:
    void kapcsolodva();
    void ClientNewMessage(Command *str);
    void ConnectedToServer();
    void ConnectionError(QAbstractSocket::SocketError socketError);
    void debugs(QString);

public slots:
    void ClientSendMessage(Command *str);
    void connectHost(QString ip, quint16 port);
    void kapcs();

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();

private:
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    QNetworkSession *networkSession;
};

#endif
