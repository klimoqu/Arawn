#include "arawnheader.h"

PixmapObjectItem::PixmapObjectItem(const QPixmap &pixmap, QObject *parent) :
    QObject(parent), QGraphicsPixmapItem(pixmap)
{
}
