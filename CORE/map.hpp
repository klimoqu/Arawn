#pragma once

#include <fstream>
#include <string>

#include "arawnheader.h"

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
    void Upload(int id);
    QList<Bomb*> bombs;


public:
    Map(int id,Player* player_0,Player* player_1);
    Map(int id,Player* player_0,Player* player_1,Player* player_2);
    Map(int id,Player* player_0,Player* player_1,Player* player_2,Player* player_3);
    int GetPlayersNumber(){return playersnumber;}
    void Save(std::ostream &o);
    void Load(std::istream &i);
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

signals:
    void BombPlanted(uchar x, uchar y,uchar id);
    void FieldBlasted(uchar x, uchar y, uchar id, uchar direction);
    void PlayerDied(uchar id);
    void PlayerMoved(uchar id,uchar direction);
    void PlayerBlasted(uchar id);
    void FieldChanged(uchar x, uchar y, uchar type);

public slots:
    void DeleteThis(Bomb *b)
    {
        bombs.removeAll(b);
        delete b;
    }
    void InputCommand(Command &c){}
    void FieldBurning(uchar x, uchar y, uchar id,uchar direction)
    {
        emit FieldBlasted(x,y,id,direction);
    }
};
