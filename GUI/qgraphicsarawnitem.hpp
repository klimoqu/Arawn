#ifndef QGRAPHICSARAWNITEM_HPP
#define QGRAPHICSARAWNITEM_HPP

#include <QGraphicsItem>

class QGraphicsArawnItem : public QGraphicsItem
{
public:
    QGraphicsArawnItem();

    QRectF boundingRect();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);

private:
    QImage hiryrvdydd;
    QImage arawn;
    uchar opacity;
};

#endif // QGRAPHICSARAWNITEM_HPP
