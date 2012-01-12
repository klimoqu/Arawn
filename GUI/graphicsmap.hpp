#ifndef GRAPHICSMAP_HPP
#define GRAPHICSMAP_HPP

#include <QtGui>
#include "CORE/field.hpp"
#include "CORE/game.hpp"
#include "GUI/graphicsplayer.hpp"

class GraphicsMap : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsMap(Game *_g, QState *_mapState, QState *_cupState, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



signals:
    void commanding(uchar c);
    void bombPlanted();
    void bombBlasted();
    void playerDied();
    void playerBlasted();

public slots:
    void setMapIDs();
    void plantBomb(uchar x, uchar y, uchar player);
//    void plantBonus(uchar x, uchar y, uchar type);
    void blastField(uchar x, uchar y, uchar player, uchar dir);
    void blastingOut(uchar x, uchar y);
    void changeField(uchar x, uchar y, uchar type);
//    void moveBomb()
    void movePlayer(uchar player, uchar dir);
    void diePlayer(uchar player);
    void blastPlayer(uchar player);

private:
    uchar mapIDs[20][13];
    QImage* fPixmaps[10];

    GraphicsPlayer* players[4];
    uchar playersCount;

    QList<GraphicsBomb*> bombs;

    uchar burning[20][13];
    QMap<uchar, QImage*> bImages;

    Game *g;
    QState *mapState;
    QState *cupState;
};


class GraphicsTimer : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsTimer() {
        timer.setSingleShot(false);
        connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
        QImage observer("res/observer.png");
        clock = (observer.copy(40, 0, 40, 40));
        noclock = (observer.copy(80, 0, 40, 40));
        font = qApp->font();
        font.setPixelSize(50);
    }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void setTimer(int roundTime);
    void tick();

private:
    QImage clock;
    QImage noclock;
    QTimer timer;
    ushort secs;
    QFont font;
};

#endif // GRAPHICSMAP_HPP




















