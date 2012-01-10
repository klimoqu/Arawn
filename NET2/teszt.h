#ifndef TESZT_H
#define TESZT_H

#include "client.h"
#include "server.h"
#include "command.hpp"

class teszt : public QObject
{
    Q_OBJECT
public:
    teszt();

signals:
    void starts(QString ip, quint16 port);
    void sendMessageWithClient1(Command*);
    void sendMessageWithClient2(Command*);
    void sendMessageWithClient3(Command*);
    void sendMessageWithClient4(Command*);

public slots:
    void sendMyMessage1();
    void sendMyMessage2();
    void sendMyMessage3();
    void sendMyMessage4();
    void fromServer(Command*);
    void fromClient(Command*);
    void conn1();
    void conn2();
    void conn3();
    void conn4();
    void showDebugs(QString);

private slots:
    void displayError(QAbstractSocket::SocketError socketError);

protected:
    Server s;
    Client c1;
    Client c2;
    Client c3;
    Client c4;

};

#endif // TESZT_H
