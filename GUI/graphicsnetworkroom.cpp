#include "graphicsnetworkroom.hpp"

GraphicsNetworkRoom::GraphicsNetworkRoom(Game *_g, QState *_ownState, QState *_gameState)
{
    g = _g;
    title = ArawnSettings::instance()->defaultIPAddress.toString();
    playerStrs[0] = tr("#1 player");
    playerStrs[1] = tr("#2 player");
    playerStrs[2] = tr("#3 player");
    playerStrs[3] = tr("#4 player");
    playerNums = g->GetPlayers().size();
    for(uchar i = 0; i < playerNums; i++) playerNames[i]=g->GetPlayers()[i];
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(40);
    nameFont = qApp->font();
    nameFont.setPixelSize(30);
    _ownState->machine()->addDefaultAnimation(new QPropertyAnimation(this, "pos"));
    _ownState->assignProperty(this, "pos", QPointF(0,0));
    _ownState->addTransition(g, SIGNAL(GameStarted()), _gameState);
}

QRectF GraphicsNetworkRoom::boundingRect() const
{
    return QRectF(-366, -270, 650, 373);
}

void GraphicsNetworkRoom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    // Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    painter->drawText(QRectF(-300,-266, 600, 66).translated(4,4), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-300,-266, 600, 66), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));


    painter->restore();
}
