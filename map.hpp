#pragma once

#include <QObject>
#include <fstream>
#include <vector>
#include <string>

#include "field.hpp"

class Map : public QObject
{
protected:
    std::string name;
    int id;
    int size_x;
    int size_y;
    int playersnumber;
    std::ifstream input;
    std::vector<std::vector<Field*> > Fields;
public:
    Map(int id);
    int GetX(){return size_x;}
    int GetY(){return size_y;}
    int GetPlayersNumber(){return playersnumber;}
    void Save(std::ostream &o);
    void Load(std::istream &i);
};
