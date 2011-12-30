#ifndef GRAPHICSMAP_HPP
#define GRAPHICSMAP_HPP

#include "arawnheader.h"

class GraphicsMap : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsMap(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setMapIDs(Field** &fields);

signals:
    void commanding(Command &c);
//    void bombPlanted(uchar x, uchar y, uchar player);
//    void fieldBlasting(uchar x, uchar y, uchar player, uchar dir);
//    void fielChanged(uchar x, uchar y, uchar type);
//    void playerMoved(float x, float y);
//    void playerDied(uchar player);
//    void playerBlasted(uchar player);

public slots:
    void plantBomb(uchar x, uchar y, uchar player);
//    void plantBonus(uchar x, uchar y, uchar type);
    void blastField(uchar x, uchar y, uchar player, uchar dir);
    void changeField(uchar x, uchar y, uchar type);
    void movePlayer(uchar player, uchar dir);
    void diePlayer(uchar player);
    void blastPlayer(uchar player);

private:
    uchar mapIDs[20][13];
    QPixmap* fPixmaps[10];

};

#endif // GRAPHICSMAP_HPP
