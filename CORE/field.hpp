#pragma once

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
    QTimer *qt;
    bool burning;
    Bonus *bonus;

public:

    Field(uchar x,uchar y,uchar type);
    bool HasBonus(){return bonus!=0;}
    bool IsDeadly(){return burning || type==4;}
    bool IsPermeable(){return type==2 || type==4;}
    bool IsBlastable(){return type==1 || type==3;}
    uchar GetType(){return this->type;}
    uchar GetOwner(){return id;}
    void SetBonus(Bonus *bonus);
    void SetTopNeighbours(Field *top){this->top=top;}
    void SetLeftNeighbours(Field *left){this->left=left;}
    void SetRightNeighbours(Field *right){this->right=right;}
    void SetBottomNeighbours(Field *bottom){this->bottom=bottom;}
    void StartBurn(uchar size,uchar id, uchar direction);
    Field* GetTopNeighbour(){return top;}
    Field* GetLeftNeighbour(){return left;}
    Field* GetRightNeighbour(){return right;}
    Field* GetBottomNeighbour(){return bottom;}
    Bonus* GetBonus(){return bonus;}
    void Visit(Player *player);

signals:
    void Extincted(uchar x,uchar y);
    void Boomed(uchar x,uchar y,uchar size,uchar id,uchar direction);
    void FieldChanged(uchar x,uchar y,uchar newtype);
    void BonusChanged(uchar x,uchar y, uchar type,uchar visibleorstate);

public slots:
    void Boom(uchar x,uchar y,uchar size, uchar id,uchar direction);
    void Extinction();
    void BonusTurnToVisible(){emit BonusChanged(this->x,this->y,bonus->GetType(),1);}
    void BonusPickUpOrDestroyed(){emit BonusChanged(this->x,this->y,bonus->GetType(),2);}
};
