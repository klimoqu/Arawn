#ifndef QGRAPHICSFADEITEM_HPP
#define QGRAPHICSFADEITEM_HPP

#include <QObject>
#include "arawnheader.h"

class QGraphicsTransitionItem : public QObject, QGraphicsItem
{
    Q_OBJECT
public:
    explicit QGraphicsTransitionItem(QColor &firstColor, QColor &targetColor,
                               uchar &step, QObject *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void transitionFinished();

public slots:

private:
    QColor firstColor;
    QColor targetColor;
    uchar step;
};

#endif // QGRAPHICSFADEITEM_HPP
