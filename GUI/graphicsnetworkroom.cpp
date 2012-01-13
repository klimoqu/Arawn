#include "GUI/graphicsnetworkroom.hpp"

GraphicsNetworkRoom::GraphicsNetworkRoom()
{
    playerStrs[0] = tr("#1 player");
    playerStrs[1] = tr("#2 player");
    playerStrs[2] = tr("#3 player");
    playerStrs[3] = tr("#4 player");
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(40);
    nameFont = qApp->font();
    nameFont.setPixelSize(30);
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
    painter->drawText(QRectF(-300,-266, 600, 66).translated(4,4), ArawnSettings::instance()->defaultIPAddress, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-300,-266, 600, 66), ArawnSettings::instance()->defaultIPAddress, QTextOption(Qt::AlignCenter | Qt::AlignTop));

    // játékosok
    if(playerNums >= 0){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(itemFont);
        painter->drawText(QRectF(-360, -166, 233, 66).translated(3,3), playerStrs[0], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-360, -166, 233, 66), playerStrs[0], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(nameFont);
        painter->drawText(QRectF(-100, -166, 266, 66).translated(2,3), playerNames[0], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-100, -166, 266, 66), playerNames[0], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(200, -166, 133, 66).translated(2,3), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default1Color, "Blank"), QTextOption(Qt::AlignCenter));
        painter->setPen(QRgb(ArawnSettings::instance()->default1Color.toInt()));
        painter->drawText(QRectF(200, -166, 133, 66), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default1Color, "Blank"), QTextOption(Qt::AlignCenter));
    }
    if(playerNums >= 1){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(itemFont);
        painter->drawText(QRectF(-360, -100, 233, 66).translated(3,3), playerStrs[1], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-360, -100, 233, 66), playerStrs[1], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(nameFont);
        painter->drawText(QRectF(-100, -100, 266, 66).translated(2,3), playerNames[1], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-100, -100, 266, 66), playerNames[1], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(200, -100, 133, 66).translated(2,3), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default2Color, "Blank"), QTextOption(Qt::AlignCenter));
        painter->setPen(QRgb(ArawnSettings::instance()->default2Color.toInt()));
        painter->drawText(QRectF(200, -100, 133, 66), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default2Color, "Blank"), QTextOption(Qt::AlignCenter));
    }
    if(playerNums >= 2){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(itemFont);
        painter->drawText(QRectF(-360, -33, 233, 66).translated(3,3), playerStrs[2], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-360, -33, 233, 66), playerStrs[2], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(nameFont);
        painter->drawText(QRectF(-100, -33, 266, 66).translated(2,3), playerNames[2], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-100, -33, 266, 66), playerNames[2], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(200, -33, 133, 66).translated(2,3), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default3Color, "Blank"), QTextOption(Qt::AlignCenter));
        painter->setPen(QRgb(ArawnSettings::instance()->default3Color.toInt()));
        painter->drawText(QRectF(200, -33, 133, 66), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default3Color, "Blank"), QTextOption(Qt::AlignCenter));
    }
    if(playerNums >= 3){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(itemFont);
        painter->drawText(QRectF(-360, 33, 233, 66).translated(3,3), playerStrs[3], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-360, 33, 233, 66), playerStrs[3], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(nameFont);
        painter->drawText(QRectF(-100, 33, 266, 66).translated(2,3), playerNames[3], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-100, 33, 266, 66), playerNames[3], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(200, 33, 133, 66).translated(2,3), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default4Color, "Blank"), QTextOption(Qt::AlignCenter));
        painter->setPen(QRgb(ArawnSettings::instance()->default4Color.toInt()));
        painter->drawText(QRectF(200, 33, 133, 66), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default4Color, "Blank"), QTextOption(Qt::AlignCenter));
    }

    painter->restore();
}

void GraphicsNetworkRoom::pushPlayer()
{
    playerNums = g->GetPlayers().size()-1;
    for(uchar i = 0; i < playerNums; i++) playerNames[i]=g->GetPlayers()[i];
    update(boundingRect());
}

void GraphicsNetworkRoom::setParams(Game *_g, QState *_ownState, QState *_gameState)
{
    g = _g;
    playerNums = g->GetPlayers().size()-1;
    for(uchar i = 0; i < playerNums; i++) playerNames[i]=g->GetPlayers()[i];
    _ownState->assignProperty(this, "visible", true);
    _gameState->assignProperty(this, "visible", false);
    _ownState->addTransition(g, SIGNAL(GameStarted(int)), _gameState);
    connect(g, SIGNAL(GameStarted(int)), this, SLOT(deleteLater()));
    connect(g, SIGNAL(NewPlayer()), this, SLOT(pushPlayer()));
}















