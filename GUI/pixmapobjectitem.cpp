#include "pixmapobjectitem.hpp"

PixmapObjectItem::PixmapObjectItem(const QPixmap &pixmap, QObject *parent) :
    QObject(parent), QGraphicsPixmapItem(pixmap)
{
}
