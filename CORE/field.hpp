#pragma once

#include <QObject>
#include <iostream>
#include <sstream>
#include "player.hpp"

class Field : public QObject
{
    Q_OBJECT
    Field *top,*right,*left,*bottom;
    unsigned int id,x,y;
    bool permeable;

public:
    Field(){}

    Field(unsigned int id, unsigned int x,unsigned int y)
    {
        this->x=x;
        this->y=y;
        this->id=id;
        std::stringstream ss;
        ss<<id;
        std::string stringid;
        ss>>stringid;
    }
    bool IsPermeable()
    {
        return permeable;
    }
    void SetNeighbours(Field *left, Field *top, Field *right, Field *bottom)
    {
        this->top=top;
        this->left=left;
        this->right=right;
        this->bottom=bottom;
    }
    Field* GetTopNeighbour()
    {
        return top;
    }
    Field* GetLeftNeighbour()
    {
        return left;
    }
    Field* GetRightNeighbour()
    {
        return right;
    }
    Field* GetBottomNeighbour()
    {
        return bottom;
    }
    void Save(std::ostream &o)
    {
        o<<x<<" "<<y<<" "<<id<<std::endl;
    }
    void Load();
    void Enter(Player *player);
    void Exit(Player *player);

public slots:
    void Boom(uchar x,uchar y,int size, uchar diretion);
};
