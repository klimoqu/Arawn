#include "CORE/game.hpp"
#include <math.h>

Game::Game(int playersnumber,bool server,uchar playerid)
{
    this->playersnumber=playersnumber;
    this->bombtimeout=2500;
    this->server=server;
    this->playerid=playerid;
    map=new Map(playersnumber);
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
        emit KlientValidate(ret);
    }
    else
    {
        Command ret=Command(playerid,1,c);
        emit KlientValidate(ret);
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
        map->player_moved(c.GetPlayerId(),c.GetMessage());
    }
    if(c.GetMessageType()==2)//plant
    {
        map->bomb_planted((c.GetMessage()/256)%256,c.GetMessage()%256,c.GetPlayerId());
    }
    if(c.GetMessageType()==3)//boom
    {
        map->field_blasted((c.GetMessage()/256)%256,c.GetMessage()%256,c.GetPlayerId(),(c.GetMessage()/(256*256))%256);
    }
    if(c.GetMessageType()==4)//kioltas
    {
        map->field_excinted((c.GetMessage()/256)%256,c.GetMessage()%256);
    }
    if(c.GetMessageType()==5)//die/blast
    {
        if(c.GetMessage()==0){map->player_died(c.GetPlayerId(),c.GetMessage());}
        if(c.GetMessage()==1){map->player_blasted(c.GetPlayerId());}
    }
    if(c.GetMessageType()==6)
    {
    }
}
