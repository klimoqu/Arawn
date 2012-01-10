#ifndef LISTENTHREAD_H
#define LISTENTHREAD_H

#include<QThread>
#include<QTcpSocket>
#include "command.hpp"


class ListenThread : public QThread
{
    Q_OBJECT

public:

    ListenThread(QObject *parent, QTcpSocket *_tcpSocket);
    void run();

signals:
    void ListenThreadMessage(Command *str);
    void debugsListenThread(QString);

public slots:

protected:
    QTcpSocket *tcpSocket;

private:

};

#endif // LISTENTHREAD_H
