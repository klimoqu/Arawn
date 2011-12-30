#pragma once

#include <QObject>

/// Absztrakt játékos osztály
class Player : public QObject
{
    Q_OBJECT
protected:
    /// Játékos neve, amely megjelenik a listában is.
    QString *pName;
    /// Játékos X koordinátája
    float pXcoord;
    /// Játékos Y koordinátája
    float pYcoord;
    /// Játékos sebessége (1-)
    uchar pSpeed;
    /// Játékos által egyszerre lerakható bombák száma (1-)
    uchar pBombsNum;
    /// Játékos által lerakott bombák ereje (1-)
    uchar pBombPower;
    /// A játékos tud-e bombát a lerakás pillanatában dobni? (kezdetben false)
    bool pCanPush;
    /// A játékos él-e
    bool live;
    uchar id;

public:
    Player(uchar id,QString Name)
    {
        this->pName=Name;
        this->id=id;
    }
    uchar GetId(){return id;}
    void SetStartPosition(float x, float y);
    void Move(int direction);
    bool IsAlive(){return live;}
    float GetX(){return pXcoord;}
    float GetY(){return pYcoord;}
    uchar GetBombSize(){return pBombPower;}
    bool CanDrop(){return pBombsNum>0;}
    void Plant(int bombtiemout);

private slots:
    void CanDropNow(){pBombsNum++;}
public slots:
    void Die();
};
