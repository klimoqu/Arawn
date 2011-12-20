#ifndef PIXMAPOBJECTITEM_HPP
#define PIXMAPOBJECTITEM_HPP

#include "arawnheader.h"

class PixmapObjectItem : public QGraphicsObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PixmapObjectItem(QPixmap *pixmap = 0, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

private:

};

#endif // PIXMAPOBJECTITEM_HPP
