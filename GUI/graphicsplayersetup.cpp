#include "GUI/graphicsplayersetup.hpp"

GraphicsNPSetup::GraphicsNPSetup(QAbstractState *_backState, QState *_ownState, QState *_nextState)
{
    title = tr("Players setup");
    names[0] = tr("Local player");
    names[1] = tr("#1 Network player");
    names[2] = tr("#2 Network player");
    names[3] = tr("#3 Network player");
    selected = 1;
    playersnum = 4;
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(30);
}

QRectF GraphicsNPSetup::boundingRect() const
{
    return QRectF(-366, -270, 650, 330);
}

void GraphicsNPSetup::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    // Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    painter->drawText(QRectF(-233,-266, 466, 66).translated(4,4), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-233,-266, 466, 66), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));

    //Kijelölés
    painter->setBrush(QColor(150,100,150,100));
    painter->setPen(Qt::NoPen);
    switch(selected){
    case 0:
        painter->drawRect(-366, -150, 300, 50);
        break;
    case 2:
        painter->drawRect(166, -150, 115, 50);
        break;
    case 10:
        painter->drawRect(-366, -100, 300, 50);
        break;
    case 20:
        painter->drawRect(-366, -50, 300, 50);
        break;
    case 30:
        painter->drawRect(-366, 0, 300, 50);
        break;
    }

    //Jelzők
    painter->setFont(itemFont);

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-366, -150, 300, 50).translated(2,3), names[0], QTextOption(Qt::AlignLeading));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-366, -150, 300, 50), names[0], QTextOption(Qt::AlignLeading));

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-366, -100, 300, 50).translated(2,3), names[1], QTextOption(Qt::AlignLeading));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-366, -100, 300, 50), names[1], QTextOption(Qt::AlignLeading));

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-366, -50, 300, 50).translated(2,3), names[2], QTextOption(Qt::AlignLeading));
    if(playersnum > 2)    painter->setPen(QColor(50, 150, 200));
    else                  painter->setPen(QColor(95, 95, 100));
    painter->drawText(QRectF(-366, -50, 300, 50), names[3], QTextOption(Qt::AlignLeading));

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-366, 0, 300, 50).translated(2,3), names[4], QTextOption(Qt::AlignLeading));
    if(playersnum > 3)    painter->setPen(QColor(50, 150, 200));
    else                  painter->setPen(QColor(95, 95, 100));
    painter->drawText(QRectF(-366, 0, 300, 50), names[4], QTextOption(Qt::AlignLeading));

    //Név
    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-33, -150, 166, 50).translated(2,3), (selected == 1 ? (ArawnSettings::instance()->defaultPlayer1Name).toString()+"_" : (ArawnSettings::instance()->defaultPlayer1Name).toString()), QTextOption(Qt::AlignLeading));
    painter->drawLine(-33, -110, 133, -110);
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-33, -150, 166, 50), (selected == 1 ? (ArawnSettings::instance()->defaultPlayer1Name).toString()+"_" : (ArawnSettings::instance()->defaultPlayer1Name).toString()), QTextOption(Qt::AlignLeading));
    painter->drawLine(-31, -108, 135, -108);

    // Szín



    painter->restore();
}






















