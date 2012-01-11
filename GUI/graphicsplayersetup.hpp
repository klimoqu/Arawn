#ifndef GRAPHICSPLAYERSETUP_HPP
#define GRAPHICSPLAYERSETUP_HPP

#include <QtGui>
#include "arawnsettings.hpp"

//class GraphicsPlayerSetup : public QGraphicsObject
//{
//    Q_OBJECT
//public:
//    GraphicsPlayerSetup() {}

//    QRectF boundingRect() const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//private:
//    QString title;
//    QString humanPlayer;
//    QString cpu1Player;
//    QString cpu2Player;
//    QString cpu3Player;
//    QString hPlayerName;
//    QString c1PlayerName;
//    QString c2PlayerName;
//    QString c3PlayerName;
//};


class GraphicsNPSetup : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsNPSetup(QAbstractState *_backState, QState *_ownState);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void previousState();

public slots:
    void setGrabKeyboard();
    void setUnGrabKeyboard();

private:
    void keyPressEvent(QKeyEvent *event);

    QString title;
    QString names[4];
    QFont titFont;
    QFont itemFont;
    uchar selected; // 0, 1, 2: local; 10: #1; 20: #2; ...
};

#endif // GRAPHICSPLAYERSETUP_HPP























