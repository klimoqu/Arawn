#include "bonus.hpp"
/*
  1 bomba erő növelése
  2 bomba erő csökkentése
  3 bombák számának növelése
  4 bombák számának csökkentése
  5 sebesség növelés
  6 sebesség csökkentés
  7 láthatatlanság
  8 ellenkező írány
  9 besülés
*/
Bonus::Bonus(uchar type)
{
    this->type=type;
}
void Bonus::Pickup(Player *owner)
{
    switch(type)
    {
    case 1:
        owner->IncrementBombSize();
        break;
    case 2:
        owner->DecrementBombSize();
        break;
    case 3:
        owner->IncrementBombNumber();
        break;
    case 4:
        owner->DecrementBombNumber();
        break;
    case 5:
        owner->SpeedUp();
        break;
    case 6:
        owner->SpeedDown();
        break;
    case 7:
        owner->Invisibility();
        break;
    case 8:
        owner->InversControl();
        break;
    case 9:
        owner->SetFail(true);
        break;
    default:
        break;
    }
    emit PickUpOrDestroyed();
    delete this;
}

