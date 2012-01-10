//#include <QtGui>
#include <QtNetwork>

#include "client.h"


Client::Client(QObject *parent)
: QObject(parent), networkSession(0)
{

    // find out which IP to connect to
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    tcpSocket = new QTcpSocket();

    connect(tcpSocket, SIGNAL(connected()), this, SIGNAL(ConnectedToServer()));

    //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));

//    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
//            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SIGNAL(ConnectionError(QAbstractSocket::SocketError)));

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        networkSession->open();
    }

}

Client::~Client()
{
    tcpSocket->disconnectFromHost();
}

void Client::kapcs()
{
    qDebug() << "kapcsolódva";
}

void Client::ClientSendMessage(Command *str)
{
    emit debugs("clientsendmessage start");
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << str->GetPlayerId() << str->GetMessageType() << str->GetMessage();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    if(tcpSocket->write(block)==block.size())
    {
    }
    tcpSocket->flush();
    emit debugs("clientsendmessage stop");
}

void Client::connectHost(QString ip, quint16 port)
{
    tcpSocket->abort();

    tcpSocket->connectToHost(ip, port, QIODevice::ReadWrite);

    clientthread *cth = new clientthread(this, tcpSocket);

    connect(cth, SIGNAL(debugsClientThread(QString)), this, SIGNAL(debugs(QString)));

    connect(cth, SIGNAL(ClientThreadMessage(Command*)), this, SIGNAL(ClientNewMessage(Command*)));

//    connect(tcpSocket, SIGNAL(readyRead()), cth, SLOT(start()));

    cth->start();
}

void Client::displayError(QAbstractSocket::SocketError socketError)
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
        qDebug() << tr("Fortune Client") <<
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString());
    }
}

void Client::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();

    qDebug()<<tr("This examples requires that you run the "
                            "Fortune Server example as well.");
}

bool Client::isServer()
{
    return false;
}
