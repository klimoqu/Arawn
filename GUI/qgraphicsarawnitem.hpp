#ifndef QGRAPHICSARAWNITEM_HPP
#define QGRAPHICSARAWNITEM_HPP

#include "arawnheader.h"

class QGraphicsArawnItem : public QGraphicsItem
{
public:
    QGraphicsArawnItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    QImage hiryrvdydd;
    QImage arawn;
    uchar opacity;

};

#endif // QGRAPHICSARAWNITEM_HPP
