#include "graphicsmap.hpp"

GraphicsMap::GraphicsMap(QGraphicsItem *parent) : QGraphicsObject(parent)
{

}

QRectF GraphicsMap::boundingRect() const
{
    return QRectF(-400, -260, 800, 520);
}

void GraphicsMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

void GraphicsMap::plantBomb(uchar x, uchar y, uchar player)
{
}

void GraphicsMap::blastField(uchar x, uchar y, uchar player, uchar dir)
{
}

void GraphicsMap::changeField(uchar x, uchar y, uchar type)
{
}

void GraphicsMap::movePlayer(uchar player, uchar dir)
{
}

void GraphicsMap::diePlayer(uchar player)
{
}

void GraphicsMap::blastPlayer(uchar player)
{
}

void GraphicsMap::setMapIDs(Field **&fields)
{

}
