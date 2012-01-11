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
void Player::Invisibility()
{
    qtvisible.stop();
    qtvisible.setSingleShot(true);
    qtvisible.start(6000);
    connect(&qtvisible,SIGNAL(timeout()),this,SIGNAL(ReturnToVisible()));
}

