#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>

/// Absztrakt játékos osztály
class Player : public QObject
{
    Q_OBJECT
public:
    Player();

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
    bool pCanDrop;
    /// A játékos tudja-e a lerakott bombákat ellökni? (kezdetben false)
    bool pCanPush;

};

#endif // PLAYER_HPP
