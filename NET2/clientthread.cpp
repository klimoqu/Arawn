#include "clientthread.h"
#include "command.hpp"

clientthread::clientthread(QObject *parent, QTcpSocket *uj):QThread(parent)
{
    tcpSocket = uj;
}

void clientthread::run()
{
    emit debugsClientThread("clientThread start");
    quint16 blockSize = 0;
    while(true)
    {
        QDataStream in(tcpSocket);
        in.setVersion(QDataStream::Qt_4_0);
        if (blockSize == 0)
        {
            while(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            {
                return;
            }
            in >> blockSize;
        }
        if (tcpSocket->bytesAvailable() < (quint64)blockSize)
        {
            return;
        }
        uchar a,b;
        int c;
        in >> a >> b >> c;
        Command co(a,b,c);

        emit ClientThreadMessage(&co);

        blockSize = 0;
    }
    emit debugsClientThread("clientThread stop");
}
