#include "qgraphicsarawnitem.hpp"

QGraphicsArawnItem::QGraphicsArawnItem()
{
    hiryrvdydd = QImage("res/hiryrvdydd.png");
    arawn = QImage("res/Arawn.png");
    opacity = 255;
}


QRectF QGraphicsArawnItem::boundingRect() const
{
    return QRectF(-(scene()->width()/2), -(scene()->height()/2), scene()->width(), scene()->height());
}


void QGraphicsArawnItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QImage image(QSize(scene()->width(), scene()->height()), QImage::Format_ARGB32_Premultiplied);
    QPainter imagePainter(&image);
    imagePainter.drawImage(0, -300, arawn);
    imagePainter.setBrush(QBrush(QColor(0, 0, 0, opacity)));
    imagePainter.drawRect(0,0,100,100);

    painter->drawImage(0, 0, image);
}

void QGraphicsArawnItem::advance(int phase)
{
    if(!phase)
        return;

    if(opacity > 50)
        opacity--;

    if(opacity == 0)
        return;

}

