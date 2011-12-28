#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <QList>

#include "CORE/field.hpp"
#include "CORE/bomb.hpp"

class Map : public QObject
{
protected:
    std::string name;
    int id;
    int size_x;//field darabok
    int size_y;//field darabok
    std::ifstream input;
    std::vector<std::vector<Field*> > Fields;
    Player* players[];
    uchar playersnumber;
    void Upload(int id);
    QList<Bomb*> bombs;


public:
    Map(int id,Player* player_0,Player* player_1);
    Map(int id,Player* player_0,Player* player_1,Player* player_2);
    Map(int id,Player* player_0,Player* player_1,Player* player_2,Player* player_3);
    int GetX(){return size_x;}
    int GetY(){return size_y;}
    int GetPlayersNumber(){return playersnumber;}
    void Save(std::ostream &o);
    void Load(std::istream &i);
    Player* GetPlayer(uchar id){if (id>=playersnumber) return 0;else return players[id];}
    Field* GetField(uchar x, uchar y){return Fields[x][y];}
    void AddBomb(Bomb* b){bombs.push_back(b);}

public slots:
    void DeleteThis(Bomb *b)
    {
        bombs.removeAll(b);
        delete b;
    }
};
