#pragma once

#include <fstream>
#include <string>
#include "CORE/field.hpp"
#include "CORE/bomb.hpp"
#include "CORE/player.hpp"
#include "CORE/command.hpp"

class Map : public QObject
{
    Q_OBJECT
protected:
    std::string name;
    int id;
    std::ifstream input;
    Field* Fields[20][13];
    Player* players[4];
    uchar playersnumber;
    QList<Bomb*> bombs;


public:
    void Upload(int id);
    Map(int playersnumber);

    int GetPlayersNumber(){return playersnumber;}
    Player* GetPlayer(uchar id){if (id>=playersnumber) return 0;else return players[id];}
    Field* GetField(uchar x, uchar y){return Fields[x][y];}
    void AddBomb(Bomb* b){bombs.push_back(b);}
    Bomb* GetBomb(int i){return bombs[i];}

    void bomb_planted(uchar x, uchar y,uchar id)
    {
        emit BombPlanted(x,y,id);
    }
    void field_blasted(uchar x, uchar y, uchar id, uchar direction)
    {
        emit FieldBlasted(x,y,id,direction);
    }
    void player_died(uchar id)
    {
        emit PlayerDied(id);
    }
    void player_moved(uchar id,uchar direction)
    {
        emit PlayerMoved(id,direction);
    }
    void player_blasted(uchar id)
    {
        emit PlayerBlasted(id);
    }
    void field_changed(uchar x, uchar y, uchar type)
    {
        emit FieldChanged(x,y,type);
    }
    void field_excinted(uchar x, uchar y)
    {
        emit FieldExcinted(x,y);
    }

signals:
    void BombPlanted(uchar x, uchar y,uchar id);
    void FieldBlasted(uchar x, uchar y, uchar id,uchar direction);
    void FieldExcincted(uchar x, uchar y);
    void PlayerDied(uchar id);
    void PlayerMoved(uchar id,uchar direction);
    void PlayerBlasted(uchar id);
    void FieldChanged(uchar x, uchar y, uchar type);
    void FieldExcinted(uchar x,uchar y);

    void ServerCommand(Command c);

public slots:
    void DeleteThis(Bomb *b)
    {
        bombs.removeAll(b);
        delete b;
    }
    void FieldBurning(uchar x, uchar y, uchar id,uchar direction)
    {
        emit FieldBlasted(x,y,id,direction);
    }
    void FieldExcinguish(uchar x, uchar y)
    {
        emit FieldExcincted(x,y);
    }
    void PlayerDie(uchar id)
    {
        emit PlayerDied(id);
    }
    void PlayerBlast(uchar id)
    {
        emit PlayerDied(id);
    }
};
