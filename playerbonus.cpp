#include "playerbonus.hpp"

PlayerBonus::PlayerBonus(QObject *parent, Player *player) :
    QObject(parent)
{
    this->player = player;
}
void PlayerBonus::execute()
{

}
