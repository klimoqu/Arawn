#include "GUI/graphicsplayersetup.hpp"

GraphicsNPSetup::GraphicsNPSetup(QAbstractState *_backState, QState *_ownState, QState *_nextState)
{
    title = tr("Players setup");
    names[0] = tr("Local player");
    names[1] = tr("#1 Network player");
    names[2] = tr("#2 Network player");
    names[3] = tr("#3 Network player");
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(40);
}

QRectF GraphicsNPSetup::boundingRect() const
{
    return QRectF(-366, -270, 640, 430);
}

void GraphicsNPSetup::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    // Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    painter->drawText(QRectF(-266,-266, 533, 66).translated(4,4), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-266,-266, 533, 66), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));

    painter->restore();
}

