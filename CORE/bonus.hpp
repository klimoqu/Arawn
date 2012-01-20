#pragma once

#include <QObject>
#include <QtCore>
#include "player.hpp"

class Bonus : public QObject
{
    Q_OBJECT
    uchar type;
    bool usable;
public:
    Bonus(uchar type);
	void TurnVisible(){emit TurnedVisible();}
    bool IsUsable(){return usable;}
    uchar GetType(){return type;}
    void Pickup(Player *owner);
signals:
    void TurnedVisible();
    void PickUpOrDestroyed();
public slots:

};
