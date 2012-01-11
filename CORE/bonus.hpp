#pragma once

#include <QObject>
#include "player.hpp"

class Bonus : public QObject
{
    Q_OBJECT
    uchar type;
    bool usable;
public:
    Bonus(uchar type);
    bool IsUsable(){return usable;}
    uchar GetType(){return type;}
    void Pickup(Player *owner);
signals:
    void TurnVisible();
    void PickUpOrDestroyed();
public slots:

};
