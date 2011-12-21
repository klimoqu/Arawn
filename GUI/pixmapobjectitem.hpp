#ifndef PIXMAPOBJECTITEM_HPP
#define PIXMAPOBJECTITEM_HPP

#include "arawnheader.h"

class PixmapObjectItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal z READ zValue WRITE setZValue)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(QPointF transformOriginPoint READ transformOriginPoint WRITE setTransformOriginPoint)
    Q_PROPERTY(QGraphicsEffect *effect READ graphicsEffect WRITE setGraphicsEffect)

public:
    explicit PixmapObjectItem(const QPixmap &pixmap, QObject *parent = 0);

signals:

public slots:

};

#endif // PIXMAPOBJECTITEM_HPP
