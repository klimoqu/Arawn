#ifndef GRAPHICSMAP_HPP
#define GRAPHICSMAP_HPP

#include <QtGui>
#include "../CORE/field.hpp"
#include "../CORE/game.hpp"
#include "graphicsplayer.hpp"

class GraphicsMap : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsMap(QState *_mapState, QState *_cupState, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



signals:
    void commanding(uchar c);
    void bombPlanted();
    void bombBlasted();
    void playerDied();
    void playerBlasted();

public slots:
//    void setMapIDs(int ido);
    void plantBomb(uchar x, uchar y, uchar player);
    void plantBonus(uchar x, uchar y, uchar type);
    void deleteBonus(uchar x, uchar y, uchar type);
    void blastField(uchar x, uchar y, uchar , uchar dir);
    void blastingOut(uchar x, uchar y);
    void changeField(uchar x, uchar y, uchar type);
    void movePlayer(uchar player, uchar dir);
    void diePlayer(uchar player, uchar murderid);
    void blastPlayer(uchar player);
//    void startPlayerFrom(uchar id, uchar x, uchar y);
    void invisiblePlayer(uchar playerid);
    void visiblePlayer(uchar playerid);
    void destroyField(uchar x,uchar y);
    void animateBombs();
    void manageGrabKeyboard();
    void deleteBomb(uchar x,uchar y);

private:
    void keyPressEvent(QKeyEvent *event);

    //uchar mapIDs[20][13];
    QImage* fPixmaps[10];

    GraphicsPlayer* players[4];
    uchar playersCount;

    QList<GraphicsBomb*> bombs;
    QList<GraphicsBonus*> bonuses;

    uchar burning[20][13];
    QMap<uchar, QImage*> bImages;
    QTimer *bombAnimator;

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
        font.setPixelSize(40);
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


class GraphicsCup : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsCup(QSound *atEnd);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

signals:
    void backToMenu();

public slots:
    void updateList();
    void playerWon(QString name);
    void becameVisible();

private:
    QSound *sound;
    QStringList winners;
    QImage bgnd;
    QImage cupImg;
    QFont font;
    QFont listFont;
};

#endif // GRAPHICSMAP_HPP




















