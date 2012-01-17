#include "client.hpp"

Client::Client(QString name)
{
    this->name=name;
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SIGNAL(Connected()));
    connect(socket, SIGNAL(connected()), this, SLOT(SendUsernameToServer()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(ConnectionFailed()));
}

void Client::connectToServer(QString address)
{
    socket->connectToHost(address,(quint16)28300);
    socket->waitForConnected();
}

void Client::readyRead()
{
    while(socket->canReadLine())
	{
		QString line = QString::fromUtf8(socket->readLine()).trimmed();
		qDebug() << "Read line:" << line;
		QRegExp usersRegex("^/usernames:(.*)$");
		QRegExp commandRegex("^/command:(.*)$");
		if(usersRegex.indexIn(line) != -1)		///az auth rész
		{
			players = usersRegex.cap(1).split(",");
			emit refreshPlayers();
		}
		else if(commandRegex.indexIn(line) != -1)									///command jön a servertõl
		{
			uchar id,type;
			int msg;
			QStringList command = commandRegex.cap(1).split(' ');
			id=(uchar)command.at(0).toInt();
			type=(uchar)command.at(0).toInt();
			msg=command.at(0).toInt();
			emit CommandReceivedFromServer(Command(id,type,msg));
		}
		else																		///egyéb hülyeség jön a klienstõl
		{
			qDebug() << "hülyeség jött";
		}
	}
}
void Client::SendCommandToServer(Command c)
{
    QByteArray command;
    command.append((uchar)c.GetPlayerId());
    command.append((uchar)c.GetMessageType());
    command.append(QByteArray::number(c.GetMessage()));
    socket->write(command);
    socket->flush();
}
void Client::SendUsernameToServer()
{
	socket->write(QString("/me:"+name+'\n').toUtf8());
    socket->flush();
}
