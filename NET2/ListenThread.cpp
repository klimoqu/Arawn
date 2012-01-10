#include "ListenThread.h"
#include <QtNetwork>

ListenThread::ListenThread(QObject *parent, QTcpSocket *_tcpSocket)
    :QThread(parent)
{
    tcpSocket = _tcpSocket;
}

void ListenThread::run()
{
    emit debugsListenThread("listenthread start");
    quint16 blockSize = 0;
    while(true)
    {
        QDataStream in(tcpSocket);
        in.setVersion(QDataStream::Qt_4_0);
        if (blockSize == 0)
        {
            if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            {
                return;
            }
            in >> blockSize;
        }
        if (tcpSocket->bytesAvailable() < (qint64)blockSize)
        {
            return;
        }
        uchar a,b;
        int c;
        in >> a >> b;
        in >> c;
        Command co(a,b,c);

        emit ListenThreadMessage(&co);

        blockSize = 0;
    }
    emit debugsListenThread("listenthread stop");
}
