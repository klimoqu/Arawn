#include "servernet.hpp"
#include <QRegExp>
Servernet::Servernet(QObject *parent):QTcpServer(parent)
{
	players.clear();
	playernumber=4;
	if(this->listen(QHostAddress::Any,(quint16)28300))
	{
		emit ServerIsRunning();
	}
	else {
		emit ServerNetworkError();
	}
}
void Servernet::incomingConnection(int socketfd)
{
	QTcpSocket *client=new QTcpSocket(this);
	client->setSocketDescriptor(socketfd);
	clients.insert(client);

	connect(client,SIGNAL(readyRead()),this,SLOT(readyRead()));
	connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
}
QStringList Servernet::GetPlayers()
{
	QStringList playerslist;
	playerslist<<name;
	if(players.size()>0)foreach(QString player,players.values())playerslist<<player;
	return playerslist;
}
void Servernet::readyRead()
{
	QTcpSocket *client =(QTcpSocket*)sender();
	while(client->canReadLine())
	{
		QString line = QString::fromUtf8(client->readLine()).trimmed();
		QRegExp meRegex("^/me:(.*)$");
		QRegExp commandRegex("^/command:(.*)$");
		if(meRegex.indexIn(line) != -1 && players.size()<=this->playernumber)		///az auth rész
		{
			QString user = meRegex.cap(1);
			players.insert(client,user);
			Command c((uchar)clients.size(),(uchar)255,(int)0);
			client->write(c.ToString().toUtf8());
			client->flush();
			emit NewPlayerConnected();
			sendusernames();
			if(players.size()==this->playernumber)emit AllPlayersConnected();
		}
		else if(commandRegex.indexIn(line) != -1)									///command jön a klienstől
		{
			uchar id,type;
			int msg;
			QStringList command = commandRegex.cap(1).split(' ');
			id=(uchar)command.at(0).toInt();
			type=(uchar)command.at(1).toInt();
			msg=command.at(2).toInt();
			emit CommandReceivedFromClients(Command(id,type,msg));
		}
		else																		///egyéb hülyeség jön a klienstől
		{
			qDebug() << "hülyeség jött";
		}
	}

}
void Servernet::disconnected()
{
	QTcpSocket *client =(QTcpSocket*)sender();
	clients.remove(client);
	QString user=players[client];
	players.remove(client);
	sendusernames();
}
void Servernet::sendusernames()
{
	QStringList playerslist=GetPlayers();
	foreach(QTcpSocket *client,clients)
	{
		client->write(QString("/usernames:"+playerslist.join(",")+'\n').toUtf8());
		client->flush();
	}
}
void Servernet::SendCommandToClients(Command c)
{
	foreach(QTcpSocket *client,clients)
	{
		client->write(c.ToString().toUtf8());
		client->flush();
	}
}

