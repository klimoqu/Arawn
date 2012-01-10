#include "connection.h"
#include <QHostAddress>
#include "command.hpp"

connection::connection(QTcpSocket *parent):QTcpSocket(parent)
{
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    out2 = new QDataStream(&block, QIODevice::WriteOnly);
    out2->setVersion(QDataStream::Qt_4_0);
    setOpenMode(QIODevice::ReadWrite);
}

void connection::send(Command str)
{
    (*out2) << (quint16)0;
    (*out2) << str.GetPlayerId() << str.GetMessageType() << str.GetMessage();
      out2->device()->seek(0);
    (*out2) << (quint16)(block.size()-sizeof(quint16));
    this->write(block);
    this->flush();
}
