#include "game.hpp"
#include <QTimer>
#include <math.h>

Game::Game(QString address)
{
	this->settings=aSetInstance;
	map=0;
	serverconnection=0;
	clientconnection=new Client(settings->defaultPlayer1Name);
	connect(this,SIGNAL(ClientValidate(Command)),clientconnection,SLOT(SendCommandToServer(Command)));
	connect(clientconnection,SIGNAL(CommandReceivedFromServer(Command)),this,SLOT(ServerExecute(Command)));
	connect(clientconnection,SIGNAL(Connected()),this,SIGNAL(Connected()));
	connect(clientconnection,SIGNAL(ConnectionFailed()),this,SIGNAL(ConnectionFailed()));
	connect(clientconnection, SIGNAL(refreshPlayers()), this, SIGNAL(RefreshPlayers()));
}

Game::Game(uchar playersnumber,int bombtimeout,ArawnSettings *settings,bool survive)
{
	this->cup=0;
	this->survive=survive;
	this->settings=settings;
	this->playersnumber=playersnumber;
	this->bombtimeout=bombtimeout;
	this->playerid=0;
	gametimer=new QTimer(this);
	destroymap=new QTimer(this);
	map=new Map(playersnumber,settings);
	map->Upload(1);
	clientconnection=0;
	serverconnection=new Servernet();
	serverconnection->SetPlayerNumber(playersnumber);
	serverconnection->SetLocalPlayername(settings->defaultPlayer1Name);
	connect(map,SIGNAL(ServerCommand(Command)),this,SIGNAL(ServerValidate(Command)));
	connect(this,SIGNAL(ClientValidate(Command)),this,SLOT(ClientExecute(Command)));
	connect(this,SIGNAL(ServerValidate(Command)),serverconnection,SLOT(SendCommandToClients(Command)));
	connect(this,SIGNAL(ServerValidate(Command)),this,SLOT(ServerExecute(Command)));
	connect(serverconnection,SIGNAL(CommandReceivedFromClients(Command)),this,SLOT(ClientExecute(Command)));
	connect(serverconnection,SIGNAL(ServerIsRunning()),this,SIGNAL(ServerIsRunning()));
	connect(serverconnection,SIGNAL(NewPlayerConnected()),this,SIGNAL(NewPlayer()));
	connect(serverconnection,SIGNAL(ServerNetworkError()),this,SIGNAL(ConnectionFailed()));
	connect(serverconnection,SIGNAL(AllPlayersConnected()),this,SLOT(AllReady()));
	connect(this,SIGNAL(FieldDestroyedByMap(uchar,uchar)),map,SIGNAL(FieldDestroyed(uchar,uchar)));
}

void Game::SetCup(Cup *cup)
{
	if(this->cup)delete this->cup;
	this->cup=cup;
	if(survive)
	{
		connect(this,SIGNAL(PlayerSurvived(uchar)),this->cup,SLOT(PlayerSurvive(uchar)));
	}
	else
	{
		connect(this,SIGNAL(PlayerDied(uchar,uchar)),this->cup,SLOT(PlayerDie(uchar,uchar)));
	}
	connect(cup,SIGNAL(PlayerPointChanged(uchar,int)),this,SLOT(ChangePlayerPoint(uchar,int)));
	connect(cup,SIGNAL(PlayerWonTheCup(uchar,QString)),this,SLOT(PlayerWinTheCup(uchar,QString)));
}

void Game::ConnectToServer(QString str)
{
	clientconnection->connectToServer(str);
}

QStringList Game::GetPlayers()
{
	if(clientconnection)return clientconnection->GetPlayers();
	else return serverconnection->GetPlayers();
}
uchar Game::GetPlaysersNumber()
{
	return GetPlayers().size();
}
void Game::NewGame(int id)
{
	destroymap->stop();
	gametimer->stop();
	this->map->Upload(id);
	sendmap();
	map->SetPlayersStartPoints();
	QTimer::singleShot(1000, this, SLOT(StartGame()));
}
void Game::MakeCommand(uchar c)
{
	if(c==255)
	{
		Command ret=Command(playerid,2,0);
		emit ClientValidate(ret);
	}
	else
	{
		Command ret=Command(playerid,1,c);
		emit ClientValidate(ret);
	}
}
void Game::validate(Command c)
{
	
	if( c.GetMessageType()!=1 && c.GetMessageType()!=2 )
	{
		return;
	}
	if(map->GetPlayer(c.GetPlayerId())==0)
	{
		return;
	}
	if(!(map->GetPlayer(c.GetPlayerId())->IsAlive()) && c.GetMessageType()!=5)
	{
		return;
	}
	Player *player=map->GetPlayer(c.GetPlayerId());

	//Move parancsok:
	if(c.GetMessageType()==1)
	{
		if(!map->GetPlayer(c.GetPlayerId())->CanControll())
		{
			switch(c.GetMessage()%256)
			{
			case 0:
				c=Command(c.GetPlayerId(),c.GetMessageType(),c.GetMessage()+3);
				break;
			case 1:
				c=Command(c.GetPlayerId(),c.GetMessageType(),c.GetMessage()+1);
				break;
			case 2:
				c=Command(c.GetPlayerId(),c.GetMessageType(),c.GetMessage()-1);
				break;
			case 3:
				c=Command(c.GetPlayerId(),c.GetMessageType(),c.GetMessage()-3);
				break;
			default:
				break;
			}
		}
		uchar x=player->GetX();
		uchar y=player->GetY();
		Field *field=map->GetField(x,y);

		if(c.GetMessage()%256==0 && (field->GetLeftNeighbour()==0 || !field->GetLeftNeighbour()->IsPermeable()))
		{
			return;
		}
		if(c.GetMessage()%256==1 && (field->GetTopNeighbour()==0 || !field->GetTopNeighbour()->IsPermeable()))
		{

			return;
		}
		if(c.GetMessage()%256==2 && (field->GetBottomNeighbour()==0 || !field->GetBottomNeighbour()->IsPermeable()))
		{
			return;
		}
		if(c.GetMessage()%256==3 && (field->GetRightNeighbour()==0 || !field->GetRightNeighbour()->IsPermeable()))
		{
			return;
		}
	}
	if(c.GetMessageType()==2)
	{
		c=Command(c.GetPlayerId(),c.GetMessageType(),map->GetPlayer(c.GetPlayerId())->GetX()*256+map->GetPlayer(c.GetPlayerId())->GetY());
	}
	//Bomba lerakás:
	if(c.GetMessageType()==2 && !map->GetPlayer(c.GetPlayerId())->CanDrop())
	{
		return;
	}
	emit ServerValidate(c);
	execute(c);
}
void Game::execute(Command c)
{
	// Mozgás
	if(c.GetMessageType()==1)
	{
		map->GetPlayer(c.GetPlayerId())->Move(c.GetMessage()%256);
		if(map->GetField(map->GetPlayer(c.GetPlayerId())->GetX(),map->GetPlayer(c.GetPlayerId())->GetY())->IsDeadly())
		{
			map->PlayerDie(c.GetPlayerId(),map->GetField(map->GetPlayer(c.GetPlayerId())->GetX(),map->GetPlayer(c.GetPlayerId())->GetY())->GetOwner());
		}
		if(map->GetPlayer(c.GetPlayerId())->GetSpeed()>1 && c.GetMessage()<256)
		{
			QTimer *qt=new QTimer(this);
			qt->setSingleShot(true);
			qt->start(50);
			QTimer::singleShot(50,this, SLOT(WaitingCommandExecute()));
			tempcommands.insert(qt,Command(c.GetPlayerId(),c.GetMessageType(),65536+256*map->GetPlayer(c.GetPlayerId())->GetSpeed()+c.GetMessage()));
		}
		if(c.GetMessage()>65536 && (c.GetMessage()/256)%256>0)
		{
			QTimer *qt=new QTimer(this);
			qt->setSingleShot(true);
			qt->start(50);
			connect(qt,SIGNAL(timeout()), this, SLOT(WaitingCommandExecute()));
			tempcommands.insert(qt,Command(c.GetPlayerId(),c.GetMessageType(),c.GetMessage()-256));
		}
		map->GetField(map->GetPlayer(c.GetPlayerId())->GetX(),map->GetPlayer(c.GetPlayerId())->GetY())->Visit(map->GetPlayer(c.GetPlayerId()));
	}
	//Bomba lerakás:
	if(c.GetMessageType()==2 && map->GetPlayer(c.GetPlayerId())->CanDrop())
	{
		uchar x=map->GetPlayer(c.GetPlayerId())->GetX();
		uchar y=map->GetPlayer(c.GetPlayerId())->GetY();
		map->AddBomb(new Bomb(x,y,map->GetPlayer(c.GetPlayerId())->GetBombSize(),c.GetPlayerId(),bombtimeout,map->GetPlayer(c.GetPlayerId())->CanFail()));
		map->GetPlayer(c.GetPlayerId())->Plant();
	}
}
void Game::WaitingCommandExecute()
{
	validate(tempcommands[(QTimer*)sender()]);
	tempcommands.remove((QTimer*)sender());
	delete (QTimer*)sender();
}
void Game::AllReady()
{
	cup->AddPlayer(settings->defaultPlayer1Name);
	for(uchar i=0;i<playersnumber-1;i++)cup->AddPlayer(serverconnection->GetPlayers().at(i));
	sendmap();
	map->SetPlayersStartPoints();
	QTimer::singleShot(1000, this, SLOT(StartGame()));
}
void Game::StartGame()
{
	emit ServerValidate(Command(255,251,settings->roundTimeDefault.toInt()));
	emit ServerValidate(Command(255,251,settings->roundTimeDefault.toInt()));
	QTimer::singleShot(settings->roundTimeDefault.toInt()*1000, this, SLOT(TimeIsOver()));
}
void Game::sendmap()
{
	for(uchar i=0;i<20;i++)
		for(uchar j=0;j<13;j++)
		{
			emit ServerValidate(Command(255,250,map->GetField(i,j)->GetType()*256*256+i*256+j));
		}
		map->bonusupload();
}
void Game::PlayerWinTheCup(uchar playerid,QString name)
{
	emit PlayerWonTheCup(name);
	emit ServerValidate(Command(playerid,253,0));
}
void Game::TimeIsOver()
{
	if(survive)
	{
		GameIsEnd();
	}
	else
	{
		act=0;
		destroymap->setSingleShot(false);
		destroymap->start(100);
		connect(destroymap,SIGNAL(timeout()), this, SLOT(DestroyField()));
	}
}
void Game::DestroyField()
{
	emit ServerValidate(Command(255,6,256*256*4+256*act/13+act%13));
	emit FieldDestroyedByMap(act/13,act%13);
	act++;
	if (act==260)
	{
		destroymap->stop();
		GameIsEnd();
	}
}
void Game::GameIsEnd()
{
	emit ServerValidate(Command(255,252,0));
	if(survive)for(uchar i=0;i<playersnumber;i++)
		if(map->GetPlayer(i)->IsAlive())
			emit PlayerSurvived(i);
}
void Game::clientsync(Command c)
{
	switch(c.GetMessageType())
	{
	case 0:
		{
			emit PlayerPointChanged(c.GetPlayerId(),c.GetMessage());
			break;
		}
	case 1://move
		{
			emit PlayerMoved(c.GetPlayerId(),c.GetMessage());
			break;
		}
	case 2://plant
		{
			emit BombPlanted((c.GetMessage()/256)%256,c.GetMessage()%256,c.GetPlayerId());
			break;
		}
	case 3://boom
		{
			emit FieldBlasted((c.GetMessage()/256)%256,c.GetMessage()%256,c.GetPlayerId(),(c.GetMessage()/(256*256))%256);
			break;
		}
	case 4://kioltas
		{
			emit FieldExcinted((c.GetMessage()/256)%256,c.GetMessage()%256);
			break;
		}
	case 5://die/blast
		{
			if(c.GetMessage()!=256){emit PlayerDied(c.GetPlayerId(),c.GetMessage());}
			else{emit PlayerBlasted(c.GetPlayerId());}
			break;
		}
	case 6://mezőváltozás
		{
			fields[(c.GetMessage()/256)%256][c.GetMessage()%256]=(c.GetMessage()/(256*256))%256;
			emit FieldChanged((c.GetMessage()/256)%256,c.GetMessage()%256,(c.GetMessage()/(256*256))%256);
			break;
		}
	case 7://bónuszok
		{
			switch(c.GetMessage()/(256*256*256))
			{
			case 1:
				emit BonusTurnVisible((c.GetMessage()/256)%256,c.GetMessage()%256,(c.GetMessage()/(256*256))%256);
				break;
			case 2:
				emit BonusTurnInvisible((c.GetMessage()/256)%256,c.GetMessage()%256,(c.GetMessage()/(256*256))%256);
				break;
			case 3:
				emit PlayerTurnVisible(c.GetPlayerId());
				break;
			case 4:
				emit PlayerTurnInvisible(c.GetPlayerId());
				break;
			default:
				break;
			}
			break;
		}
	case 250://pályaszinkron
		{
			fields[(c.GetMessage()/256)%256][c.GetMessage()%256]=(c.GetMessage()/(256*256))%256;
			break;
		}
	case 251://játék kezdete
		{
			emit GameStarted(c.GetMessage());
			break;
		}
	case 252://játék vége
		{
			emit GameOver();
			break;
		}
	case 253://a győztes
		{
			switch(c.GetMessage())
			{
			case 0:
				emit PlayerWonTheCup(GetPlayers()[c.GetPlayerId()]);
				break;
			case 1:
				emit PlayerWonTheRound(GetPlayers()[c.GetPlayerId()]);
				if(map){destroymap->stop();GameIsEnd();}
				break;
			}
			break;
		}
	case 254://alaphelyzetbe állítás
		{
			emit SetPlayerStartPosition(c.GetPlayerId(),(c.GetMessage()/256)%256,c.GetMessage()%256);
			break;
		}
	case 255://azonosítás
		{
			playerid=c.GetPlayerId();
			qDebug()<<"auth"<<(int)c.GetPlayerId();
			break;
		}
	default:
		{
			break;
		}
	}
}
