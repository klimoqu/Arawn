#include "CORE/player.hpp"

void Player::Move(uchar direction)
{
    switch(direction)
    {
        case 0:
            pYcoord--;
            break;
        case 1:
            pXcoord--;
            break;
        case 2:
            pXcoord++;
            break;
        case 3:
            pYcoord++;
            break;
        default:
        break;
    }
}
void Player::SetStartPosition(uchar x, uchar y)
{
    pXcoord=x;
    pYcoord=y;
    live=true;
    blastable=false;
    pBombsNum=1;
    pBombPower=1;
}
void Player::DieAndBlast(uchar id,uchar x, uchar y,uchar dir)
{
    if( pXcoord==x && pYcoord==y && live)
    {
        emit Died(this->id,id);
        blastable=true;
        live=false;
    }
    if( pXcoord==x && pYcoord==y && blastable)
    {
        emit Blasted(this->id);
        blastable=false;
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
        emit Died(this->id,255);
        live=false;
    }
}
void Player::Invisibility()
{
    emit ChangeVisibility(this->id,true);
    t_visible.stop();
    t_visible.setSingleShot(true);
    t_visible.start(6000);
    connect(&t_visible,SIGNAL(timeout()),this,SLOT(returntovisible()()));
}
void Player::InversControl()
{
    isoppositecontrol=true;
    t_oppositecontrol.stop();
    t_oppositecontrol.setSingleShot(true);
    t_oppositecontrol.start(6000);
    connect(&t_oppositecontrol,SIGNAL(timeout()),this,SLOT(returntonormalcontrol()));
}
void Player::returntonormalcontrol()
{
    isoppositecontrol=false;
}
