#include "CORE/game.hpp"
#include <QTimer>
#include <math.h>

Game::Game(QString address)
{
    map=0;
    serverconnection=0;
    clientconnection=new Client(address);

    connect(this,SIGNAL(ClientValidate(Command)),clientconnection,SLOT(SendCommandToServer(Command)));
    connect(clientconnection,SIGNAL(CommandReceivedFromServer(Command)),this,SLOT(ServerExecute(Command)));
    connect(clientconnection,SIGNAL(Connected()),this,SIGNAL(Connected()));
    connect(clientconnection,SIGNAL(ConnectionFailed()),this,SIGNAL(ConnectionFailed()));
}

Game::Game(uchar playersnumber,int bombtimeout,ArawnSettings *settings)
{
    this->settings=settings;
    this->playersnumber=playersnumber;
    this->bombtimeout=bombtimeout;
    this->playerid=0;
    map=new Map(playersnumber,settings);
    clientconnection=0;
    serverconnection=new Servernet();
    serverconnection->SetPlayerNumber(playersnumber);

    connect(map,SIGNAL(ServerCommand(Command)),this,SLOT(ServerExecute(Command)));
    connect(this,SIGNAL(ClientValidate(Command)),this,SLOT(ClientExecute(Command)));
    connect(this,SIGNAL(ServerValidate(Command)),serverconnection,SLOT(SendCommandToClients(Command)));
    connect(this,SIGNAL(ServerValidate(Command)),this,SLOT(ServerExecute(Command)));
    connect(serverconnection,SIGNAL(CommandReceivedFromClients(Command)),this,SLOT(ClientExecute(Command)));
    connect(serverconnection,SIGNAL(ServerIsRunning()),this,SIGNAL(ServerIsRunning()));
    connect(serverconnection,SIGNAL(NewPlayerConnected(QString)),this,SIGNAL(NewPlayer(QString)));
    connect(serverconnection,SIGNAL(ServerNetworkError()),this,SIGNAL(ConnectionFailed()));
}
void Game::SetCup(Cup *cup)
{
    this->cup=cup;
    connect(this,SIGNAL(PlayerDied(uchar,uchar)),this->cup,SLOT(PlayerDie(uchar,uchar)));
}
QStringList Game::GetPlayers()
{
    if(clientconnection)clientconnection->GetPlayers();
    else serverconnection->GetPlayers();
}
void Game::NewGame(int id)
{
    this->map->Upload(id);

}
void Game::MakeCommand(uchar c)
{
    if(c==255)
    {
        Command ret=Command(playerid,2,map->GetPlayer(playerid)->GetX()*256+map->GetPlayer(playerid)->GetY());
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
        if(map->GetField(map->GetPlayer(c.GetPlayerId())->GetX(),map->GetPlayer(c.GetPlayerId())->GetY())->IsBurn())
        {
            map->PlayerDie(c.GetPlayerId(),map->GetField(map->GetPlayer(c.GetPlayerId())->GetX(),map->GetPlayer(c.GetPlayerId())->GetY())->GetOwner());
        }
        if(map->GetPlayer(c.GetPlayerId())->GetSpeed()>1 && c.GetMessage()<256)
        {
            QTimer *qt;
            qt->setSingleShot(true);
            qt->start(50);
            connect(qt,SIGNAL(timeout()), this, SLOT(WaitingCommandExecute()));
            tempcommands.insert(qt,Command(c.GetPlayerId(),c.GetMessageType(),65536+256*map->GetPlayer(c.GetPlayerId())->GetSpeed()+c.GetMessage()));
        }
        if(c.GetMessage()>65536 && (c.GetMessage()/256)%256>0)
        {
            QTimer *qt;
            qt->setSingleShot(true);
            qt->start(50);
            connect(qt,SIGNAL(timeout()), this, SLOT(WaitingCommandExecute()));
            tempcommands.insert(qt,Command(c.GetPlayerId(),c.GetMessageType(),c.GetMessage()-256));
        }
    }
    //Bomba lerakás:
    if(c.GetMessageType()==2 && map->GetPlayer(c.GetPlayerId())->CanDrop())
    {
        uchar x=map->GetPlayer(c.GetPlayerId())->GetX();
        uchar y=map->GetPlayer(c.GetPlayerId())->GetY();
        map->AddBomb(new Bomb(x,y,map->GetPlayer(c.GetPlayerId())->GetBombSize(),bombtimeout,map->GetPlayer(c.GetPlayerId())->CanFail()));
        map->GetPlayer(c.GetPlayerId())->Plant();
    }
}
void Game::WaitingCommandExecute()
{
    validate(tempcommands[(QTimer*)sender()]);
    tempcommands.remove((QTimer*)sender());
    delete (QTimer*)sender();
}
void Game::clientsync(Command c)
{
    if(c.GetMessageType()==1)//move
    {
        emit PlayerMoved(c.GetPlayerId(),c.GetMessage());
    }
    if(c.GetMessageType()==2)//plant
    {
        emit BombPlanted((c.GetMessage()/256)%256,c.GetMessage()%256,c.GetPlayerId());
    }
    if(c.GetMessageType()==3)//boom
    {
        emit FieldBlasted((c.GetMessage()/256)%256,c.GetMessage()%256,c.GetPlayerId(),(c.GetMessage()/(256*256))%256);
    }
    if(c.GetMessageType()==4)//kioltas
    {
        emit FieldExcinted((c.GetMessage()/256)%256,c.GetMessage()%256);
    }
    if(c.GetMessageType()==5)//die/blast
    {
        if(c.GetMessage()!=256){emit PlayerDied(c.GetPlayerId(),c.GetMessage());}
        else{emit PlayerBlasted(c.GetPlayerId());}
    }
    if(c.GetMessageType()==6)
    {
        emit FieldChanged((c.GetMessage()/256)%256,c.GetMessage()%256,(c.GetMessage()/(256*256))%256);
    }
    if(c.GetMessageType()==7)
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
    }
    if(c.GetMessageType()==255)
    {
        this->playerid=c.GetPlayerId();
    }
}
