#include "CORE/game.hpp"
#include <math.h>

Game::Game(QString address)
{
    this->server=false;
    map=0;
    serverconnection=0;
    clientconnection=new Client(address);
    connect(this,SIGNAL(ClientValidate(Command)),clientconnection,SLOT(SendCommandToServer(Command)));
    connect(clientconnection,SIGNAL(CommandReceivedFromServer(Command)),this,SLOT(ServerExecute(Command)));
}

Game::Game(uchar playersnumber,int bombtimeout)
{
    this->playersnumber=playersnumber;
    this->bombtimeout=bombtimeout;
    this->server=true;
    this->playerid=0;
    map=new Map(playersnumber);
    connect(map,SIGNAL(ServerCommand(Command)),this,SLOT(ServerExecute(Command)));
    clientconnection=0;
    serverconnection=new Servernet();
    serverconnection->SetPlayerNumber(playersnumber);

    connect(serverconnection,SIGNAL(CommandReceivedFromClients(Command)),this,SLOT(ClientExecute(Command)));
    connect(this,SIGNAL(ServerValidate(Command)),serverconnection,SLOT(SendCommandToClients(Command)));
    connect(this,SIGNAL(ServerValidate(Command)),this,SLOT(ServerExecute(Command)));
}
void Game::SetCup(Cup *cup)
{
    this->cup=cup;
    connect(this,SIGNAL(PlayerDied(uchar,uchar)),this->cup,SLOT(PlayerDie(uchar,uchar)));
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
        if(c.GetMessage()<0 || c.GetMessage()>3)
        {
            return;
        }
        float x=player->GetX();
        float y=player->GetY();
        Field *field=map->GetField(round(x),round(y));

        if(c.GetMessage()==0 && (field->GetLeftNeighbour()==0 || !field->GetLeftNeighbour()->IsPermeable()))
        {
            return;
        }
        if(c.GetMessage()==1 && (field->GetTopNeighbour()==0 || !field->GetTopNeighbour()->IsPermeable()))
        {
            return;
        }
        if(c.GetMessage()==2 && (field->GetBottomNeighbour()==0 || !field->GetBottomNeighbour()->IsPermeable()))
        {
            return;
        }
        if(c.GetMessage()==3 && (field->GetRightNeighbour()==0 || !field->GetRightNeighbour()->IsPermeable()))
        {
            return;
        }
    }
    //Bomba lerakás:
    if(c.GetMessageType()==2 && !map->GetPlayer(c.GetPlayerId())->CanDrop())
    {
        return;
    }
    emit ServerExecute(c);
    execute(c);
}
void Game::execute(Command c)
{
    // Mozgás
    if(c.GetMessageType()==1)
    {
        map->GetPlayer(c.GetPlayerId())->Move(c.GetMessage());
        if(map->GetField(map->GetPlayer(c.GetPlayerId())->GetX(),map->GetPlayer(c.GetPlayerId())->GetY())->IsBurn())
        {
            map->PlayerDie(c.GetPlayerId(),map->GetField(map->GetPlayer(c.GetPlayerId())->GetX(),map->GetPlayer(c.GetPlayerId())->GetY())->GetOwner());
        }
    }
    //Bomba lerakás:
    if(c.GetMessageType()==2 && map->GetPlayer(c.GetPlayerId())->CanDrop())
    {
        float x=map->GetPlayer(c.GetPlayerId())->GetX();
        float y=map->GetPlayer(c.GetPlayerId())->GetY();
        map->AddBomb(new Bomb(x,y,map->GetPlayer(c.GetPlayerId())->GetBombSize(),bombtimeout));
        map->GetPlayer(c.GetPlayerId())->Plant();
    }
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
        if(c.GetMessage()==0){emit PlayerDied(c.GetPlayerId(),c.GetMessage());}
        if(c.GetMessage()==1){emit PlayerBlasted(c.GetPlayerId());}
    }
    if(c.GetMessageType()==6)
    {
        emit FieldChanged((c.GetMessage()/256)%256,c.GetMessage()%256,(c.GetMessage()/(256*256))%256);
    }
    if(c.GetMessageType()==5)
    {
        this->playerid=c.GetPlayerId();
    }
}
