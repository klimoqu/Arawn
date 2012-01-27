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
    bool burning,hasbomb;
    Bonus *bonus;

public:
	~Field(){delete bonus;}
    Field(uchar x,uchar y,uchar type);
    bool HasBonus()const{return bonus!=0;}
    bool IsDeadly()const{return burning || type==4;}
    bool IsPermeable()const{return (type==2 || type==4)&&!hasbomb;}
    bool IsBlastable()const{return type==1 || type==3;}
    uchar GetType()const{return this->type;}
    uchar GetOwner()const{return id;}
	void SetBomb(bool state){hasbomb=state;}
    void SetBonus(Bonus *bonus);
    void SetTopNeighbours(Field *top){this->top=top;}
    void SetLeftNeighbours(Field *left){this->left=left;}
    void SetRightNeighbours(Field *right){this->right=right;}
    void SetBottomNeighbours(Field *bottom){this->bottom=bottom;}
    void StartBurn(uchar size,uchar id, uchar direction);
    Field* GetTopNeighbour()const{return top;}
    Field* GetLeftNeighbour()const{return left;}
    Field* GetRightNeighbour()const{return right;}
    Field* GetBottomNeighbour()const{return bottom;}
    Bonus* GetBonus()const{return bonus;}
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
