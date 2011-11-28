#include "arawnheader.h"

QGraphicsTransitionItem::QGraphicsTransitionItem(QColor &firstColor, QColor &targetColor,
                                      ushort &step, QObject *parent) :
    QObject(parent)
{
    this->currentColor = firstColor;
    stepsto = step;
    rStep = (targetColor.redF() - currentColor.redF())/((float)step);
    gStep = (targetColor.greenF() - currentColor.greenF())/((float)step);
    bStep = (targetColor.blueF() - currentColor.blueF())/((float)step);
    aStep = (targetColor.alphaF() - currentColor.alphaF())/((float)step);
}

QRectF QGraphicsTransitionItem::boundingRect() const
{
    return QRectF(-(scene()->width()/2), -(scene()->height()/2),
                  scene()->width(), scene()->height());
}

void QGraphicsTransitionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(currentColor);
    painter->setPen(Qt::NoPen);
    painter->drawRect(-(scene()->width()/2), -(scene()->height()/2),
                      scene()->width(), scene()->height());
}

void QGraphicsTransitionItem::advance(int phase)
{
    if(!phase)
        return;

    if(stepsto == 0){
        emit transitionFinished();
        return;
    }

    stepsto--;
    currentColor.setRedF(currentColor.redF() + rStep);
    currentColor.setGreenF(currentColor.greenF() + gStep);
    currentColor.setBlueF(currentColor.blueF() + bStep);
    currentColor.setAlphaF(currentColor.alphaF() + aStep);
    update(boundingRect());
}
