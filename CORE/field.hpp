#pragma once

#include <QObject>
#include <iostream>
#include <sstream>
#include "player.hpp"

class Field : public QObject
{
    Q_OBJECT
    Field *top,*right,*left,*bottom;
    uchar type,x,y;
    bool permeable;

public:
    Field(){}

    Field(uchar id, uchar x,uchar y)
    {
        this->x=x;
        this->y=y;
        this->type=type;
        std::stringstream ss;
        ss<<id;
        std::string stringid;
        ss>>stringid;
    }
    uchar GetType()
    {
        return this->type;
    }
    bool IsPermeable()
    {
        return permeable;
    }
    void SetTopNeighbours(Field *top)
    {
        this->top=top;
    }
    void SetLeftNeighbours(Field *left)
    {
        this->left=left;
    }
    void SetRightNeighbours(Field *right)
    {
        this->right=right;
    }
    void SetBottomNeighbours(Field *bottom)
    {
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
        o<<x<<" "<<y<<" "<<type<<std::endl;
    }
    void Load();
    void Enter(Player *player);
    void Exit(Player *player);

public slots:
    void Boom(uchar x,uchar y,int size, uchar diretion);
};
