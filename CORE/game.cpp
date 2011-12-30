#include "arawnheader.h"
#include <math.h>

void Game::NewGame(int id)
{
    this->map=new Map(id);
}

void Game::validate(Command c)
{
    if(map->GetPlayer(c.GetPlayerId())==0)
    {
        return;
    }
    if(!(map->GetPlayer(c.GetPlayerId())->IsAlive()))
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
    }
    //Bomba lerakás:
    if(c.GetMessageType()==2 && map->GetPlayer(c.GetPlayerId())->CanDrop())
    {
        float x=map->GetPlayer(c.GetPlayerId())->GetX();
        float y=map->GetPlayer(c.GetPlayerId())->GetY();
        map->AddBomb(new Bomb(x,y,map->GetPlayer(c.GetPlayerId())->GetBombSize(),bombtimeout));
        map->GetPlayer(c.GetPlayerId())->Plant(bombtimeout);
    }
    //Robbanások:
    if(c.GetMessageType()==3)
    {
        map->GetBomb(c.GetMessage())->Boom();
    }
}

void Game::clientsync(Command c)
{
    if(c.GetMessageType()==1)//move
    {
        emit map->PlayerMoved(c.GetPlayerId(),c.GetMessage());
    }
    if(c.GetMessageType()==2)//plant
    {
        emit map->BombPlanted((c.GetMessage()/256)%256,c.GetMessage()%256,c.GetPlayerId());
    }
    if(c.GetMessageType()==3)//boom
    {
        emit map->FieldBlasted((c.GetMessage()/256)%256,c.GetMessage()%256,c.GetPlayerId(),(c.GetMessage()/(256*256))%256);
    }
    if(c.GetMessageType()==4)//Fieldaction
    {

    }
    if(c.GetMessageType()==5)
    {
        if(c.GetMessage()==0){emit map->PlayerDied(c.GetPlayerId());}
        if(c.GetMessage()==1){emit map->PlayerBlasted(c.GetPlayerId());}
    }
}
