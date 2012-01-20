#include "graphicsmap.hpp"

#define LE 2
#define FEL 1
#define JOBBRA 3
#define BALRA 0
#define MINDEN 255

GraphicsMap::GraphicsMap(Game *_g, QState *_mapState, QState *_cupState, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    g = _g;
    mapState = _mapState;
    cupState = _cupState;

    connect(g, SIGNAL(GameStarted(int)), this, SLOT(setMapIDs()));

    connect(g, SIGNAL(BombPlanted(uchar,uchar,uchar)), this, SLOT(plantBomb(uchar,uchar,uchar)));
    connect(g, SIGNAL(FieldBlasted(uchar,uchar,uchar,uchar)), this, SLOT(blastField(uchar,uchar,uchar,uchar)));
    connect(g, SIGNAL(FieldChanged(uchar,uchar,uchar)), this, SLOT(changeField(uchar,uchar,uchar)));
    connect(g, SIGNAL(FieldExcinted(uchar,uchar)), this, SLOT(blastingOut(uchar,uchar)));
    connect(g, SIGNAL(PlayerBlasted(uchar)), this, SLOT(blastPlayer(uchar)));
    connect(g, SIGNAL(PlayerMoved(uchar,uchar)), this, SLOT(movePlayer(uchar,uchar)));
    connect(g, SIGNAL(PlayerDied(uchar,uchar)), this, SLOT(diePlayer(uchar, uchar)));
    connect(g, SIGNAL(SetPlayerStartPosition(uchar,uchar,uchar)), this, SLOT(startPlayerFrom(uchar,uchar,uchar)));
    connect(g, SIGNAL(BonusTurnVisible(uchar,uchar,uchar)), this, SLOT(plantBonus(uchar,uchar,uchar)));
    connect(g, SIGNAL(BonusTurnInvisible(uchar,uchar,uchar)), this, SLOT(deleteBonus(uchar,uchar,uchar)));
    connect(g, SIGNAL(PlayerTurnInvisible(uchar)), this, SLOT(invisiblePlayer(uchar)));
    connect(g, SIGNAL(PlayerTurnVisible(uchar)), this, SLOT(visiblePlayer(uchar)));
    connect(g, SIGNAL(FieldDestroyedByMap(uchar,uchar)), this, SLOT(destroyField(uchar,uchar)));


    fPixmaps[0] = new QImage("res/field0.png");
    fPixmaps[1] = new QImage("res/field1.png");
    fPixmaps[2] = new QImage("res/field2.png");
    fPixmaps[3] = new QImage("res/field3.png");
    fPixmaps[4] = new QImage(40,40, QImage::Format_Mono);
    fPixmaps[5] = new QImage("res/field5.png");

    QImage expl("res/explosion.png");
    bImages[LE] = new QImage(expl.copy(160, 0, 40, 40));
    bImages[BALRA] = new QImage(expl.copy(40,0,40,40));
    bImages[FEL] = bImages[LE];
    bImages[JOBBRA] = bImages[BALRA];
    bImages[MINDEN] = new QImage(expl.copy(240,0,40,40));
    bImages[LE+16] = new QImage(expl.copy(200,0,40,70));
    bImages[BALRA+16] = new QImage(expl.copy(0,0,40,40));
    bImages[FEL+16] = new QImage(expl.copy(120,0,40,40));
    bImages[JOBBRA+16] = new QImage(expl.copy(80,0,40,40));

    // TODO load players
    players[0] = new GraphicsPlayer(0, this);
    players[1] = new GraphicsPlayer(1, this);
    players[2] = new GraphicsPlayer(2, this);
    players[3] = new GraphicsPlayer(3, this);

    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            burning[i][j] = 42;
        }
    }
}

QRectF GraphicsMap::boundingRect() const
{
    return QRectF(0,0,800,520);
}

void GraphicsMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    painter->save();

    // Pálya
    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            painter->drawImage(i*40, j*40, *(fPixmaps[mapIDs[i][j]]));
        }
    }

    // Bombák
    for(uchar i = 0; i < bombs.length(); i++){
        bombs[i]->paint(painter, o, w);
    }

    // Bónuszok
    for(uchar i = 0; i < bonuses.length(); i++){
        bonuses[i]->paint(painter, o, w);
    }
	playersCount=g->GetPlaysersNumber();
	qDebug()<<"playersCount:"<<playersCount;
    // Játékosok
    for(uchar i = 0; i < playersCount; i++){
        players[i]->paint(painter, o, w);
    }

    // Tűz
    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            painter->drawImage(i*40, j*40, *(bImages[burning[i][j]]));
        }
    }
    painter->restore();
}

void GraphicsMap::plantBomb(uchar x, uchar y, uchar player)
{
    GraphicsBomb *bomb = new GraphicsBomb(player, this);
    bomb->setPos(x*40, y*40);
    scene()->addItem(bomb);
    emit bombPlanted();
    bombs.append(bomb);
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::blastField(uchar x, uchar y, uchar player, uchar dir)
{
    burning[x][y] = dir;
    /// TODO player

    for(uchar i = 0; i < bombs.length(); i++){
        if(
                (bombs[i]->x())/40 == x &&
                (bombs[i]->y())/40 == y
        ){
            delete bombs[i];
            bombs.removeAt(i);
            i--;
            emit bombBlasted();
        }
    }
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::blastingOut(uchar x, uchar y)
{
    burning[x][y] += 50;
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::changeField(uchar x, uchar y, uchar type)
{
    mapIDs[x][y] = type;
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::movePlayer(uchar player, uchar dir)
{
    players[player]->incAState();
    switch(dir){
    case BALRA:
        players[player]->setX(players[player]->x()-8);
        break;
    case FEL:
        players[player]->setY(players[player]->y()-8);
        break;
    case LE:
        players[player]->setY(players[player]->y()+8);
        break;
    case JOBBRA:
        players[player]->setX(players[player]->x()+8);
        break;
    }
    update(players[player]->x()*40-8, players[player]->y()*40-8, 56, 56);
}

void GraphicsMap::diePlayer(uchar player, uchar murderid)
{
    emit playerDied();
    players[player]->aState = 9;
    update(players[player]->boundingRect());
}

void GraphicsMap::blastPlayer(uchar player)
{
    players[player]->setVisible(false);
    emit playerBlasted();
    update(players[player]->boundingRect());
}

void GraphicsMap::setMapIDs()
{
    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            mapIDs[i][j] = g->GetFields(i, j);
        }
    }
    update(boundingRect());
}

void GraphicsMap::startPlayerFrom(uchar id, uchar x, uchar y)
{
    players[id]->setVisible(true);
    players[id]->setPos(x*40, y*40);
    update(players[id]->boundingRect());
}

void GraphicsMap::plantBonus(uchar x, uchar y, uchar type)
{
    GraphicsBonus *bonus = new GraphicsBonus(type, x*40, y*40, this);
    scene()->addItem(bonus);
    bonuses.append(bonus);
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::deleteBonus(uchar x, uchar y, uchar)
{
    for(uchar i = 0; i < bonuses.length(); i++){
        if(
                (bonuses[i]->x())/40 == x &&
                (bonuses[i]->y())/40 == y
        ){
            delete bonuses[i];
            bonuses.removeAt(i);
            i--;
        }
    }
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::invisiblePlayer(uchar playerid)
{
    players[playerid]->setVisible(false);
    update(players[playerid]->boundingRect());
}

void GraphicsMap::visiblePlayer(uchar playerid)
{
    players[playerid]->setVisible(true);
    update(players[playerid]->boundingRect());
}

void GraphicsMap::destroyField(uchar x, uchar y)
{
    mapIDs[x][y] = 4;
    update(x*40, y*40, 40, 40);
}





QRectF GraphicsTimer::boundingRect() const
{
    return QRectF(0, 0, 300, 66);
}

void GraphicsTimer::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->drawImage(0, 0, (secs > 0) ? clock : noclock);
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(font);
    painter->drawText(QRectF(45, 0, 200, 66).translated(4,4), QString(secs/60 + ":" + secs%60), QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(45, 0, 200, 66), QString(secs/60 + ":" + secs%60), QTextOption(Qt::AlignCenter));

    painter->restore();
}

void GraphicsTimer::setTimer(int roundTime)
{
    secs = roundTime;
    timer.start(1000);
}

void GraphicsTimer::tick()
{
    if(secs > 0){
        secs--;
        if(secs == 0) timer.stop();
        update(boundingRect());
    }
}




GraphicsCup::GraphicsCup(Game *_g)
{
    g = _g;
    c = g->GetCup();
    bgnd = QImage("res/fire.jpg").scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    cupImg = QImage("res/cup.png");
    font = qApp->font();
    font.setPixelSize(50);
    listFont = qApp->font();
    listFont.setPixelSize(40);
}

QRectF GraphicsCup::boundingRect() const
{
    return QRectF(-400, -300, 800, 600);
}

void GraphicsCup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->drawImage(-400, -300, bgnd);
    painter->setFont(font);
    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-300, -300, 600, 66).translated(4,4),
                      (g->IsSurvive())?(tr("Survival cup")):(tr("Murder cup")),
                      QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-300, -300, 600, 66),
                      (g->IsSurvive())?(tr("Survival cup")):(tr("Murder cup")),
                      QTextOption(Qt::AlignCenter));


    painter->setFont(listFont);
    for(uchar i = 0; i < c->GetPlayersName().length(); i++){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(-350, -166+i*50, 250, 50).translated(3,3), c->GetPlayerName(i), QTextOption(Qt::AlignLeading));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-350, -166+i*50, 250, 50), c->GetPlayerName(i), QTextOption(Qt::AlignLeading));

        for(uchar j = 0; j < c->GetPointOf(i); j++){
            painter->drawImage(-66+j*40, -160+i*50, cupImg);
        }


    }

    painter->restore();
}

void GraphicsMap::setGrabKeyboard()
{
    grabKeyboard();
}

void GraphicsMap::setUngrabKeyboard()
{
    ungrabKeyboard();
}

void GraphicsMap::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up:
        g->InputCommandFromGui(FEL);
        break;
    case Qt::Key_Down:
        g->InputCommandFromGui(LE);
        break;
    case Qt::Key_Left:
        g->InputCommandFromGui(BALRA);
        break;
    case Qt::Key_Right:
        g->InputCommandFromGui(JOBBRA);
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        g->InputCommandFromGui(255);
        break;
    }
}


































































