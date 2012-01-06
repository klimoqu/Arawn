#pragma once

#include <QObject>
#include <QTimer>
#include "math.h"

/// Absztrakt játékos osztály
class Player : public QObject
{
    Q_OBJECT
protected:
    /// Játékos X koordinátája
    float pXcoord;
    /// Játékos Y koordinátája
    float pYcoord;
    /// Játékos sebessége (1-)
    uchar pSpeed;
    /// Játékos által egyszerre lerakható bombák száma (1-)
    volatile uchar pBombsNum;
    /// Játékos által lerakott bombák ereje (1-)
    uchar pBombPower;
    /// A játékos tud-e bombát a lerakás pillanatában dobni? (kezdetben false)
    bool pCanPush;
    /// A játékos él-e
    bool live,blastable;
    uchar id;

public:
    Player(uchar id)
    {
        this->id=id;
    }
    uchar GetId(){return id;}
    void SetStartPosition(float x, float y)
    {
        pXcoord=x;
        pYcoord=y;
        live=true;
        blastable=false;
    }
    void Move(int direction);
    bool IsAlive(){return live;}
    float GetX(){return pXcoord;}
    float GetY(){return pYcoord;}
    uchar GetBombSize(){return pBombPower;}
    bool CanDrop(){return pBombsNum>0;}
    void Plant(){pBombsNum--;}

signals:
    void Died(uchar playerid,uchar murderid);
    void Blasted(uchar playerid);

public slots:
    void DieAndBlast(uchar id,uchar x, uchar y)
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
        if(id=this->id)
        {
            pBombsNum++;
        }
    }
};
