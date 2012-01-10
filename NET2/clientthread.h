#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include "command.hpp"


class clientthread : public QThread
{
    Q_OBJECT
public:
    clientthread(QObject *parent, QTcpSocket *uj);
    void run();

signals:
    void ClientThreadMessage(Command *str);
    void debugsClientThread(QString);

protected:
    QTcpSocket *tcpSocket;
};

#endif // CLIENTTHREAD_H
