#include "CORE/game.hpp"
#include <math.h>

void Game::NewGame(int id){}
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
        float x=player->GetX();
        float y=player->GetY();
        Field *field=map->GetField(round(x),round(y));

        if(c.GetMessage()==1 && (field->GetLeftNeighbour()==0 || !field->GetLeftNeighbour()->IsPermeable()))
        {
            return;
        }
        if(c.GetMessage()==2 && (field->GetTopNeighbour()==0 || !field->GetTopNeighbour()->IsPermeable()))
        {
            return;
        }
        if(c.GetMessage()==3 && (field->GetBottomNeighbour()==0 || !field->GetBottomNeighbour()->IsPermeable()))
        {
            return;
        }
        if(c.GetMessage()==4 && (field->GetRightNeighbour()==0 || !field->GetRightNeighbour()->IsPermeable()))
        {
            return;
        }
    }
    //Bomba lerakás:
    if(c.GetMessageType()==2)
    {
        float x=player->GetX();
        float y=player->GetY();
        map->AddBomb(new Bomb(x,y,map->GetPlayer(c.GetPlayerId())->GetBombSize(),timeout));
    }

    emit ServerExecute(c);
}
void Game::execute(Command c){}
