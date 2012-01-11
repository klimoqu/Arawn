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
    uchar pXcoord;
    /// Játékos Y koordinátája
    uchar pYcoord;
    /// Játékos sebessége (1-)
    uchar pSpeed;
    /// Játékos által egyszerre lerakható bombák száma (1-)
    uchar pBombsNum;
    /// Játékos által lerakott bombák ereje (1-)
    uchar pBombPower;
    /// A játékos él-e,robbantható-e,gebasz van a bombával
    bool live,blastable,fail,isvisible,isoppositecontrol;
    uchar id;
    QTimer t_visible,t_oppositecontrol;

public:
    Player(uchar id){this->id=id;}
    bool IsVisible(){return isvisible;}
    bool IsAlive(){return live;}
    bool CanFail(){if(fail){fail=false;return true;}else return fail;}
    bool CanControll(){return !isoppositecontrol;}
    bool CanDrop(){return pBombsNum>0;}
    uchar GetId(){return id;}
    uchar GetX(){return pXcoord;}
    uchar GetY(){return pYcoord;}
    uchar GetBombSize(){return pBombPower;}
    uchar GetSpeed(){return pSpeed;}
    void SetFail(bool fail){this->fail=fail;}
    void SetStartPosition(uchar x, uchar y);
    void Move(uchar direction);
    void Plant(){pBombsNum--;}
    void IncrementBombSize(){pBombPower++;}
    void DecrementBombSize(){pBombPower--;}
    void IncrementBombNumber(){pBombsNum++;}
    void DecrementBombNumber(){if(pBombsNum>1)pBombsNum--;}
    void SpeedUp(){pSpeed++;}
    void SpeedDown(){if(pSpeed>1)pSpeed--;}
    void Invisibility();
    void InversControl();

signals:
    void Died(uchar playerid,uchar murderid);
    void Blasted(uchar playerid);
    void ChangeVisibility(uchar playerid,bool visible);

private slots:
    void returntonormalcontrol();
    void returntovisible(){emit ChangeVisibility(this->id,true);}
public slots:
    void DieAndBlast(uchar id,uchar x, uchar y,uchar dir);
};
