#pragma once
#include "CORE/command.hpp"
#include <QtCore>
#include <QtNetwork/QtNetwork>
class Sockethandler : public QObject
{
    Q_OBJECT
    QTcpSocket *clientSocket;
public:
    Sockethandler(QTcpSocket *socket);
signals:
    void MessageReceived(Command c);
private slots:
    void receivemessage();
    void killme();
public slots:
    void SendMessage(Command c);
};
