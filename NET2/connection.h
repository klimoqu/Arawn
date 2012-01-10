#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include "command.hpp"

class connection : public QTcpSocket
{
public:
    connection(QTcpSocket *parent=0);
    void send(Command str);

protected:
    QByteArray block;
    QDataStream *out2;
};



#endif // CONNECTION_H
