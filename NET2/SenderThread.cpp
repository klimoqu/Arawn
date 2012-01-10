#include "SenderThread.h"
#include <QtNetwork>

SenderThread::SenderThread(QList<connection*> *_list, QObject *parent)
    : QThread(parent)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    tcpSocket = NULL;
    list = _list;
}

void SenderThread::clearMessage()
{
    mutex.lock();
    msg.clear();
    mutex.unlock();
}

void SenderThread::SenderThreadMessage(Command *str)
{
    mutex.lock();
    msg.push_back(*str);
    mutex.unlock();
}

void SenderThread::run()
{
    emit debugsSenderThread("senderThread start");
    while(!msg.isEmpty())
    {
        for(int i=0;i<list->size();i++)
        {
            tcpSocket = list->at(i);
            tcpSocket->send(msg.first());
        }
        msg.removeFirst();
    }
    emit debugsSenderThread("senderThread stop");
}
