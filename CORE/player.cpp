#include "CORE/player.hpp"

void Player::Plant(int bombtimeout)
{
    QTimer* qt=new QTimer();
    qt->setSingleShot(true);
    qt->start(bombtimeout);
    connect(qt,SIGNAL(timeout()), this, SLOT(CanDropNow()));
}
void Player::Move(int direction)
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
