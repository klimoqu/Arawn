#pragma once

#include <QObject>
#include <QTimer>
#include <iostream>
#include "player.hpp"

class Field : public QObject
{
    Q_OBJECT
    Field *top,*right,*left,*bottom;
    uchar type,x,y,state;
    QTimer qt;
    bool burning;

public:
    /*
      0 - Fal
      1 - Doboz
      2 - Fű
      3 - Nehézdoboz
      4 - Űr
      5 - Lyuk
    */

    Field(uchar id, uchar x,uchar y)
    {
        this->x=x;
        this->y=y;
        this->type=type;
        switch(id)
        {
        case 1:
            state=1;
            break;
        case 3:
            state=2;
            break;
        default:
            state=0;
        }
    }
    uchar GetType()
    {
        return this->type;
    }
    bool IsBurn()
    {
        return burning;
    }
    bool IsPermeable()
    {
        return state==0 && type!=0;
    }
    bool IsBlastable()
    {
        return state!=0 && (type==1 || type==3);
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
    void StartBurn(uchar size,uchar id, uchar direction);
signals:
    void Extincted(uchar x,uchar y);
    void Boomed(uchar x,uchar y,uchar id,uchar direction);
public slots:
    void Boom(uchar x,uchar y,uchar size, uchar id,uchar direction);
    void Extinction();
};
