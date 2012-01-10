#ifndef SenderThread_H
#define SenderThread_H

#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include "connection.h"
#include "command.hpp"

class SenderThread : public QThread
{
    Q_OBJECT

public:
    SenderThread(QList<connection*> *_list, QObject *parent);
    void run();

signals:
    void debugsSenderThread(QString);

public slots:
    void SenderThreadMessage(Command *str);
    void clearMessage();

private:
    QList<connection*> *list;
    QList<Command> msg;
    connection *tcpSocket;
    QMutex mutex;
};

#endif
