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

void Player::DieAndBlast(uchar id,uchar x, uchar y,uchar dir)
{
    if( round(pXcoord)==x && round(y)==y && live)
    {
        emit Died(this->id,id);
        blastable=true;
        live=false;
    }
    if( round(pXcoord)==x && round(y)==y && blastable)
    {
        emit Blasted(this->id);
        blastable=false;
    }
    if(id==this->id && dir==255)
    {
        pBombsNum++;
    }
}
