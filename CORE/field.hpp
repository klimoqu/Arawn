#pragma once

#include <QObject>
#include <iostream>
#include <sstream>
#include "player.hpp"

class Field : public QObject
{
protected:
    bool permeable;
    Field *top,*right,*left,*bottom;
    int id,x,y;
    bool use[];

public:
    Field(){}
    Field(int id, int x,int y,int playersnumber)
    {
        this->x=x;
        this->y=y;
        this->id=id;
        std::stringstream ss;
        ss<<id;
        std::string stringid;
        ss>>stringid;
        use=new bool[playersnumber];
    }
    void SetNeighbours(Field *top, Field *left, Field *right, Field *bottom)
    {
        this->top=top;
        this->left=left;
        this->right=right;
        this->bottom=bottom;
    }
    void Save(std::ostream &o)
    {
        o<<x<<" "<<y<<" "<<id<<std::endl;
    }
    void Load();
    void Enter(Player *player);
    void Exit(Player *player);
    bool InUse(int id){return use[id];}
};
