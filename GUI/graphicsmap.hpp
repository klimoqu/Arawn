#ifndef GRAPHICSMAP_HPP
#define GRAPHICSMAP_HPP

#include <QtGui>
#include "CORE/field.hpp"
#include "GUI/graphicsplayer.hpp"

class GraphicsMap : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsMap(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setMapIDs(Field** &fields);

signals:
    void commanding(uchar c);
    void bombPlanted();
    void bombBlasted();
    void playerDied();
    void playerBlasted();

public slots:
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

};

#endif // GRAPHICSMAP_HPP
