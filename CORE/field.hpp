#pragma once

#include <QObject>
#include <QTimer>
#include <iostream>
#include "player.hpp"

class Field : public QObject
{
    Q_OBJECT
    Field *top,*right,*left,*bottom;
    uchar x,y;
    volatile uchar id,type;
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

    Field(uchar type, uchar x,uchar y);
    uchar GetType()
    {
        return this->type;
    }
    bool IsBurn()
    {
        return burning;
    }
    uchar GetOwner()
    {
        return id;
    }
    bool IsPermeable()
    {
        return id==2;
    }
    bool IsBlastable()
    {
        return (type==1 || type==3);
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
    void FieldChanged(uchar x,uchar y,uchar newtype);
public slots:
    void Boom(uchar x,uchar y,uchar size, uchar id,uchar direction);
    void Extinction();
};
