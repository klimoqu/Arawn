#pragma once
/*
  0 - Fal
  1 - Doboz
  2 - Fű
  3 - Nehézdoboz
  4 - Űr
  5 - Lyuk
*/
#include <QObject>
#include <QTimer>
#include <iostream>
#include "player.hpp"
#include "bonus.hpp"

class Field : public QObject
{
    Q_OBJECT
    Field *top,*right,*left,*bottom;
    uchar x,y;
    uchar id,type;
    QTimer qt;
    bool burning,hasbonus;
    Bonus *bonus;

public:

    Field(uchar type, uchar x,uchar y);
    bool HasBonus(){return hasbonus;}
    bool IsBurn(){return burning;}
    bool IsPermeable(){return id==2;}
    bool IsBlastable(){return (type==1 || type==3);}
    uchar GetType(){return this->type;}
    uchar GetOwner(){return id;}
    void SetBonus(Bonus *bonus){hasbonus=true;this->bonus=bonus;}
    void SetTopNeighbours(Field *top){this->top=top;}
    void SetLeftNeighbours(Field *left){this->left=left;}
    void SetRightNeighbours(Field *right){this->right=right;}
    void SetBottomNeighbours(Field *bottom){this->bottom=bottom;}
    void StartBurn(uchar size,uchar id, uchar direction);
    Field* GetTopNeighbour(){return top;}
    Field* GetLeftNeighbour(){return left;}
    Field* GetRightNeighbour(){return right;}
    Field* GetBottomNeighbour(){return bottom;}

signals:
    void Extincted(uchar x,uchar y);
    void Boomed(uchar x,uchar y,uchar id,uchar direction);
    void FieldChanged(uchar x,uchar y,uchar newtype);
    void BonusChanged(uchar x,uchar y, uchar type,bool visible);

public slots:
    void Boom(uchar x,uchar y,uchar size, uchar id,uchar direction);
    void Extinction();
    void BonusTurnToVisible(){}
    void BonusPickUpOrDestroye(){}
};
