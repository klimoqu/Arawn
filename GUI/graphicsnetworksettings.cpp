#include "GUI/graphicsnetworksettings.hpp"
#include "arawnsettings.hpp"

GraphicsNetworkSettings::GraphicsNetworkSettings(QAbstractState *_backState, QState *_ownState, QState *_nextState)
{
    ownState = _ownState;
    backState = _backState;
    nextState = _nextState;
    lineEdit = ArawnSettings::instance()->defaultIPAddress;
    title = tr("Connect to network");
    text = tr("Enter the IP address or hostname:");
    connectText = tr("Connect");
    connecting = tr("Connecting...");
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(40);
    lineFont = qApp->font();
    lineFont.setPixelSize(30);
    selected = 1;
}

QRectF GraphicsNetworkSettings::boundingRect() const
{
    return QRectF(-360, -280, 585, 400);
}

void GraphicsNetworkSettings::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    // Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    painter->drawText(QRectF(-225,-280, 450, 75).translated(4,4), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-225,-280, 450, 75), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));

    // Szöveg
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(lineFont);
    painter->drawText(QRectF(-360,-190, 585, 50).translated(2,3), text, QTextOption(Qt::AlignLeading));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-360,-190, 585, 50), text, QTextOption(Qt::AlignLeading));

    // Sor +kijelölve?
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(lineFont);
    painter->drawText(QRectF(-360,-130, 300, 50).translated(2,3), (selected == 0 ? lineEdit.toString()+"_" : lineEdit.toString()), QTextOption(Qt::AlignLeading));
    painter->drawLine(-358, -76, 302, -76);
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-360,-130, 300, 50), (selected == 0 ? lineEdit.toString()+"_" : lineEdit.toString()), QTextOption(Qt::AlignLeading));
    painter->drawLine(-360, -78, 300, -78);

    // Gomb /kijelölve?
    if(selected == 1){
        painter->setBrush(QColor(150,100,150,100));
        painter->setPen(Qt::NoPen);
        painter->drawRect(-150,-25,300,50);
    }
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(itemFont);
    painter->drawText(QRectF(-150,-25,300,50).translated(3,3), connectText, QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-150,-25,300,50), connectText, QTextOption(Qt::AlignCenter));

    // Connecting
    if(selected == 2){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(lineFont);
        painter->drawText(QRectF(-360,35, 300, 50).translated(2,3), text, QTextOption(Qt::AlignLeading));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-360,-35, 300, 50), text, QTextOption(Qt::AlignLeading));
    }

    painter->restore();
}

void GraphicsNetworkSettings::keyDown()
{
    if(selected == 0){
        selected = 1;
        update(-360,-130, 302, 53);
        update(-150,-25,300,50);
    }
}

void GraphicsNetworkSettings::keyUp()
{
    if(selected == 1){
        selected = 0;
        update(-360,-130, 302, 53);
        update(-150,-25,300,50);
    }
}

void GraphicsNetworkSettings::keyBackspace()
{
    if(selected == 0){
        lineEdit = lineEdit.toString().section("", 0, lineEdit.toString().length()-1);
        update(-360,-130, 302, 53);
    }
}

void GraphicsNetworkSettings::keyEnter()
{
    if(selected == 0) keyDown();
    if(selected == 1) {

    }
}

void GraphicsNetworkSettings::keyEscape()
{
}
















