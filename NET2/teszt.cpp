#include "teszt.h"

void teszt::sendMyMessage1()
{
    Command *str2 = new Command(1,2,3);
//    c1.ClientSendMessage(str2);
    emit sendMessageWithClient1(str2);
}
void teszt::sendMyMessage2()
{
    Command *str3 = new Command(4,5,6);
//    c2.ClientSendMessage(str3);
    emit sendMessageWithClient2(str3);
}
void teszt::sendMyMessage3()
{
    Command *str4 = new Command(7,8,9);
//    c3.ClientSendMessage(str4);
    emit sendMessageWithClient3(str4);
}
void teszt::sendMyMessage4()
{
    Command *str5 = new Command(10,11,12);
//    c4.ClientSendMessage(str5);
    emit sendMessageWithClient4(str5);
}

void teszt::fromClient(Command *str)
{
    qDebug() << "fromClient:  ";
    qDebug() << str->GetPlayerId() << str->GetMessageType() << str->GetMessage();
}

void teszt::fromServer(Command *str)
{
    qDebug() << "fromServer:  ";
    qDebug() << str->GetPlayerId() << str->GetMessageType() << str->GetMessage();
}

void teszt::conn1(){qDebug()<< "becsatlakozva1";}
void teszt::conn2(){qDebug()<< "becsatlakozva2";}
void teszt::conn3(){qDebug()<< "becsatlakozva3";}
void teszt::conn4(){qDebug()<< "becsatlakozva4";}

void teszt::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << tr("Fortune Client") <<
                                 tr("The host was not found. Please check the "
                                    "host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << tr("Fortune Client") <<
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct.");
        break;
    default:
        qDebug() << tr("Fortune Client");/* <<
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString());*/
    }
}

void teszt::showDebugs(QString str)
{
    qDebug() << str;
}

teszt::teszt()
{
    /// debugs connect
    connect(&c1, SIGNAL(debugs(QString)), this, SLOT(showDebugs(QString)));
    connect(&c2, SIGNAL(debugs(QString)), this, SLOT(showDebugs(QString)));
//    connect(&c3, SIGNAL(debugs(QString)), this, SLOT(showDebugs(QString)));
//    connect(&c4, SIGNAL(debugs(QString)), this, SLOT(showDebugs(QString)));

    connect(&s, SIGNAL(debugs(QString)), this, SLOT(showDebugs(QString)));
    /// /

    connect(&c1, SIGNAL(ConnectedToServer()), this, SLOT(sendMyMessage1()));
    connect(&c2, SIGNAL(ConnectedToServer()), this, SLOT(sendMyMessage2()));
//    connect(&c3, SIGNAL(ConnectedToServer()), this, SLOT(sendMyMessage3()));
//    connect(&c4, SIGNAL(ConnectedToServer()), this, SLOT(sendMyMessage4()));

    connect(&c1, SIGNAL(ConnectedToServer()), this, SLOT(conn1()));
    connect(&c2, SIGNAL(ConnectedToServer()), this, SLOT(conn2()));
//    connect(&c3, SIGNAL(ConnectedToServer()), this, SLOT(conn3()));
//    connect(&c4, SIGNAL(ConnectedToServer()), this, SLOT(conn4()));

    /// clientthread
    connect(&c1, SIGNAL(ClientNewMessage(Command*)), this, SLOT(fromClient(Command*)));
    connect(&c2, SIGNAL(ClientNewMessage(Command*)), this, SLOT(fromClient(Command*)));
//    connect(&c3, SIGNAL(ClientNewMessage(Command*)), this, SLOT(fromClient(Command*)));
//    connect(&c4, SIGNAL(ClientNewMessage(Command*)), this, SLOT(fromClient(Command*)));

    /// listenthread
    connect(&s, SIGNAL(ServerNewMessage(Command*)), this, SLOT(fromServer(Command*)));

    connect(&c1, SIGNAL(ConnectionError(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(&c2, SIGNAL(ConnectionError(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
//    connect(&c3, SIGNAL(ConnectionError(QAbstractSocket::SocketError)),
//            this, SLOT(displayError(QAbstractSocket::SocketError)));
//    connect(&c4, SIGNAL(ConnectionError(QAbstractSocket::SocketError)),
//            this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(this, SIGNAL(starts(QString,quint16)), &c1, SLOT(connectHost(QString,quint16)));
    connect(this, SIGNAL(starts(QString,quint16)), &c2, SLOT(connectHost(QString,quint16)));
//    connect(this, SIGNAL(starts(QString,quint16)), &c3, SLOT(connectHost(QString,quint16)));
//    connect(this, SIGNAL(starts(QString,quint16)), &c4, SLOT(connectHost(QString,quint16)));


    connect(this, SIGNAL(sendMessageWithClient1(Command*)), &c1, SLOT(ClientSendMessage(Command*)));
    connect(this, SIGNAL(sendMessageWithClient2(Command*)), &c2, SLOT(ClientSendMessage(Command*)));
    connect(this, SIGNAL(sendMessageWithClient3(Command*)), &c3, SLOT(ClientSendMessage(Command*)));
    connect(this, SIGNAL(sendMessageWithClient4(Command*)), &c4, SLOT(ClientSendMessage(Command*)));

    qDebug()<<"Host: " << s.getIpAdress();
    qDebug()<<"Port: " << s.getPort();

    emit starts(s.getIpAdress(), s.getPort());

//    Command *str = new Command(14,15,16);

//    s.ServerSendMessage(str);
}
