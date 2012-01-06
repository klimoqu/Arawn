#include "CORE/player.hpp"


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
