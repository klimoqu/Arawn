#include "player.hpp"
#include <QtCore>
Player::Player(uchar id,uchar bombnum,uchar bombpower,uchar maxbomb,uchar maxpower)
{
    this->id=id;
    this->pBombsNum=bombnum;
	this->defaultbombs=bombnum;
    this->pBombPower=bombpower;
	this->defaultpower=bombpower;
    this->maxbomb=maxbomb;
    this->maxpower=maxpower;
	this->fail=false;
	this->live=true;
	t_visible=new QTimer(this);
	t_oppositecontrol=new QTimer(this);
}
void Player::Move(uchar direction)
{
    switch(direction)
    {
        case 0:
            pXcoord--;
            break;
        case 1:
            pYcoord--;
            break;
        case 2:
            pYcoord++;
            break;
        case 3:
            pXcoord++;
            break;
        default:
        break;
    }
}
void Player::SetStartPosition(uchar x, uchar y)
{
	this->isoppositecontrol=false;
	this->pSpeed=1;
    this->pXcoord=x;
    this->pYcoord=y;
    this->live=true;
    this->blastable=false;
	this->fail=false;
	this->pBombPower=defaultpower;
	this->pBombsNum=defaultbombs;
}
void Player::DieAndBlast(uchar x,uchar y,uchar size, uchar id,uchar dir)
{
	if( pXcoord==x && pYcoord==y && blastable)
    {
        emit Blasted(this->id);
        blastable=false;
    }
    if( pXcoord==x && pYcoord==y && live)
    {
        emit Died(this->id,id);
        blastable=true;
        live=false;
    }
    if(id==this->id && dir==255)
    {
        pBombsNum++;
    }
}
void Player::Die(uchar x, uchar y)
{
    if( pXcoord==x && pYcoord==y && live)
    {
        emit Died(id,255);
        live=false;
    }
}
void Player::Invisibility()
{
    emit ChangeVisibility(this->id,true);
    t_visible->stop();
    t_visible->setSingleShot(true);
    t_visible->start(6000);
    connect(t_visible,SIGNAL(timeout()),this,SLOT(returntovisible()()));
}
void Player::InversControl()
{
    isoppositecontrol=true;
    t_oppositecontrol->stop();
    t_oppositecontrol->setSingleShot(true);
    t_oppositecontrol->start(6000);
    connect(t_oppositecontrol,SIGNAL(timeout()),this,SLOT(returntonormalcontrol()));
}
void Player::returntonormalcontrol()
{
    isoppositecontrol=false;
}
