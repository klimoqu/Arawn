#include "arawnheader.h"

QGraphicsArawnItem::QGraphicsArawnItem()
{
    hiryrvdydd = QImage("res/hiryrvdydd.png");
    arawn = QImage("res/Arawn.png");
    opacity = 200;
}


QRectF QGraphicsArawnItem::boundingRect() const
{
    return QRectF(-(scene()->width()/2), -(scene()->height()/2), scene()->width(), scene()->height());
}


void QGraphicsArawnItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

//    painter->drawImage(0, -(arawn.height()/2), arawn);
//    painter->drawImage(QPoint(-(hiryrvdydd.width()/2), -(hiryrvdydd.height()/2)), hiryrvdydd);

    painter->drawImage(-20, -(scene()->height()/2), arawn.scaledToHeight(scene()->height(),Qt::SmoothTransformation));
    painter->drawImage(-(scene()->width()/2), -(scene()->height()/3), hiryrvdydd.scaledToWidth(scene()->width(), Qt::SmoothTransformation));

    painter->setBrush(QBrush(QColor(0, 0, 0, opacity)));
    painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}

void QGraphicsArawnItem::advance(int phase)
{
    if(!phase)
        return;

    if(opacity >= 44){
        opacity -= 45;
        update();
    }
}

