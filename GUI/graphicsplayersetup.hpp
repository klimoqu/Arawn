#ifndef GRAPHICSPLAYERSETUP_HPP
#define GRAPHICSPLAYERSETUP_HPP

#include <QtGui>
#include "../arawnsettings.hpp"

class GraphicsPlayerSetup : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsPlayerSetup(QAbstractState *_backState, QState *_ownState);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
    /// Ugorj vissza a menübe
    void previousState();

public slots:
    /// billentyű elkapása
    void setGrabKeyboard();

    /// billentyű elengedése
    void setUnGrabKeyboard();

private:
    void keyPressEvent(QKeyEvent *event);

    QString title;
    QString names[4];
    QFont titFont;
    QFont itemFont;
    uchar selected;
    uchar rows;/// 1, 2, 3, 4
};


/**
  Játékosok beállítása a hálózati játékon.
  Megadható vele a helyi játékos neve, illetve a játékosok száma
*/
class GraphicsNPSetup : public QGraphicsObject
{
    Q_OBJECT
public:

    /**
      _backState: Állapot, amelyre visszaugrik esc lenyomásakor
            (stateMenu::stateMenuHistory)
      _ownState: Saját állapot, erre kötjük be a saját tulajdonságokat
    */
    GraphicsNPSetup(QAbstractState *_backState, QState *_ownState);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    /// Ugorj vissza a menübe
    void previousState();

public slots:
    /// billentyű elkapása
    void setGrabKeyboard();

    /// billentyű elengedése
    void setUnGrabKeyboard();

private:
    void keyPressEvent(QKeyEvent *event);

    QString title; /// főcím
    QString names[4]; /// nevek(nem a játékosnevek)
    QFont titFont;
    QFont itemFont;
    uchar selected; /// 0, 1, 2: local; 10: #1; 20: #2; ...
};

#endif // GRAPHICSPLAYERSETUP_HPP























