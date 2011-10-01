#ifndef MAP_H
#define MAP_H

#include "field.h"

#include <QObject>
#include <fstream>
#include <vector>

class map : public QObject
{
protected:
    int id;
    int size_x;
    int size_y;
    int playersnumber;
    std::ifstream input;

    std::vector<std::vector<field*> > fields;
public:
    map(int id);
    int GetX(){return size_x;}
    int GetY(){return size_y;}
    int GetPlayersNumber(){return playersnumber;}
    void Save();
    void Load();
};

#endif // MAP_H
