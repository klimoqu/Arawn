#include "arawnheader.h"

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
        case 1:
            pYcoord--;
            break;
        case 2:
            pXcoord--;
            break;
        case 3:
            pXcoord++;
            break;
        case 4:
            pYcoord++;
            break;
        default:
        break;
    }
}
