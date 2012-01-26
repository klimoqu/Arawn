#include "graphicsmap.hpp"
#include "imagefactory.hpp"

#define LE 2
#define FEL 1
#define JOBBRA 3
#define BALRA 0
#define MINDEN 255

GraphicsMap::GraphicsMap(QState *_mapState, QState *_cupState, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    mapState = _mapState;
    cupState = _cupState;
    bombAnimator = new QTimer(this);
    bombAnimator->setSingleShot(false);
    bombAnimator->start(85);

    //connect(gameGlobal, SIGNAL(GameStarted(int)), this, SLOT(setMapIDs(int)), Qt::DirectConnection);

    connect(gameGlobal, SIGNAL(BombPlanted(uchar,uchar,uchar)), this, SLOT(plantBomb(uchar,uchar,uchar)));
    connect(gameGlobal, SIGNAL(FieldBlasted(uchar,uchar,uchar,uchar)), this, SLOT(blastField(uchar,uchar,uchar,uchar)));
    connect(gameGlobal, SIGNAL(FieldChanged(uchar,uchar,uchar)), this, SLOT(changeField(uchar,uchar,uchar)));
    connect(gameGlobal, SIGNAL(FieldExcinted(uchar,uchar)), this, SLOT(blastingOut(uchar,uchar)));
    connect(gameGlobal, SIGNAL(PlayerBlasted(uchar)), this, SLOT(blastPlayer(uchar)));
    connect(gameGlobal, SIGNAL(PlayerMoved(uchar,uchar)), this, SLOT(movePlayer(uchar,uchar)));
    connect(gameGlobal, SIGNAL(PlayerDied(uchar,uchar)), this, SLOT(diePlayer(uchar, uchar)));
   // connect(gameGlobal, SIGNAL(SetPlayerStartPosition(uchar,uchar,uchar)), this, SLOT(startPlayerFrom(uchar,uchar,uchar)), Qt::DirectConnection);
    connect(gameGlobal, SIGNAL(BonusTurnVisible(uchar,uchar,uchar)), this, SLOT(plantBonus(uchar,uchar,uchar)));
    connect(gameGlobal, SIGNAL(BonusTurnInvisible(uchar,uchar,uchar)), this, SLOT(deleteBonus(uchar,uchar,uchar)));
    connect(gameGlobal, SIGNAL(PlayerTurnInvisible(uchar)), this, SLOT(invisiblePlayer(uchar)));
    connect(gameGlobal, SIGNAL(PlayerTurnVisible(uchar)), this, SLOT(visiblePlayer(uchar)));
    connect(gameGlobal, SIGNAL(FieldDestroyedByMap(uchar,uchar)), this, SLOT(destroyField(uchar,uchar)));
    connect(this, SIGNAL(visibleChanged()), this, SLOT(manageGrabKeyboard()), Qt::DirectConnection);
    connect(gameGlobal, SIGNAL(DeleteBomb(uchar,uchar)), this, SLOT(deleteBomb(uchar,uchar)));
    connect(bombAnimator, SIGNAL(timeout()), this, SLOT(animateBombs()));

    fPixmaps[0] = imgFact->fieldImages[0];
    fPixmaps[1] = imgFact->fieldImages[1];
    fPixmaps[2] = imgFact->fieldImages[2];
    fPixmaps[3] = imgFact->fieldImages[3];
    fPixmaps[4] = imgFact->fieldImages[4];
    fPixmaps[5] = imgFact->fieldImages[5];

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

    players[0] = new GraphicsPlayer(0, this);
    players[1] = new GraphicsPlayer(1, this);
    players[2] = new GraphicsPlayer(2, this);
    players[3] = new GraphicsPlayer(3, this);

    players[0]->setVisible(false);
    players[1]->setVisible(false);
    players[2]->setVisible(false);
    players[3]->setVisible(false);
    players[0]->setZValue(5);
    players[1]->setZValue(6);
    players[2]->setZValue(7);
    players[3]->setZValue(8);

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
           // painter->drawImage(i*40, j*40, *(fPixmaps[mapIDs[i][j]]));
            painter->drawImage(i*40, j*40, *(fPixmaps[gameGlobal->GetFields(i, j)]));
        }
    }


    // Tűz
    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
			if(burning[i][j]!=42)painter->drawImage(i*40, j*40, *(bImages[burning[i][j]]));//itt javítottam
        }
    }
    painter->restore();
}

void GraphicsMap::plantBomb(uchar x, uchar y, uchar player)
{
    GraphicsBomb *bomb = new GraphicsBomb(x, y, player, this);
    bomb->setZValue(1);
    emit bombPlanted();    
    bombs.append(bomb);
}

void GraphicsMap::blastField(uchar x, uchar y, uchar , uchar dir)
{
    burning[x][y] = dir;
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::blastingOut(uchar x, uchar y)
{
    burning[x][y] =42;
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::changeField(uchar x, uchar y, uchar type)
{
    //mapIDs[x][y] = type;
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::movePlayer(uchar player, uchar dir)
{
    players[player]->incAState();
    players[player]->setDir(dir);
    switch(dir){
    case BALRA:
        players[player]->setX(players[player]->x()-40);
        break;
    case FEL:
        players[player]->setY(players[player]->y()-40);
        break;
    case LE:
        players[player]->setY(players[player]->y()+40);
        break;
    case JOBBRA:
        players[player]->setX(players[player]->x()+40);
        break;
    }
}
/*
//void GraphicsMap::movePlayer(uchar player, uchar dir)
//{
//    players[player]->incAState();
//    players[player]->setDir(dir);
//    switch(dir){
//    case BALRA:
//        break;
//    case FEL:
//        break;
//    case LE:
//        break;
//    case JOBBRA:
//        break;
//    }
//}
*/

void GraphicsMap::diePlayer(uchar player, uchar murderid)
{
    emit playerDied();
    players[player]->aState = 9;
}

void GraphicsMap::blastPlayer(uchar player)
{
    players[player]->setVisible(false);
    emit playerBlasted();
}

//void GraphicsMap::setMapIDs(int)
//{
//   // grabKeyboard();
///*
//    for(uchar i = 0; i < 20; i++){
//        for(uchar j = 0; j < 13; j++){
//            mapIDs[i][j] = gameGlobal->GetFields(i, j);
//        }
//    }
//*/
////    update(boundingRect());

//}

//void GraphicsMap::startPlayerFrom(uchar id, uchar x, uchar y)
//{
////    qDebug() << "Player" << id << x << y;
////    players[id]->setVisible(true);
////    players[id]->setPos(x*40, y*40);
////    update(players[id]->x(), players[id]->y(), 40, 60);
//}

void GraphicsMap::plantBonus(uchar x, uchar y, uchar type)
{
    GraphicsBonus *bonus = new GraphicsBonus(type, x, y, this);
    bonus->setZValue(0);
    bonuses.append(bonus);
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
}

void GraphicsMap::invisiblePlayer(uchar playerid)
{
    players[playerid]->setVisible(false);
}

void GraphicsMap::visiblePlayer(uchar playerid)
{
    players[playerid]->setVisible(true);
}

void GraphicsMap::destroyField(uchar x, uchar y)
{
    //mapIDs[x][y] = 4;
    update(x*40, y*40, 40, 40);
}

void GraphicsMap::animateBombs()
{
    for(uchar i = 0; i < bombs.length(); i++)
    {
        bombs[i]->incAState();
        bombs[i]->update(bombs[i]->boundingRect());
    }
}

void GraphicsMap::manageGrabKeyboard()
{
    qDebug() << "VisibleChanged to" << isVisible() ;
    if(isVisible()){
        grabKeyboard();
        players[0]->aState = 0;
        players[1]->aState = 0;
        players[2]->aState = 0;
        players[3]->aState = 0;
        switch(gameGlobal->GetPlaysersNumber())
           {
           case 4:
                       players[3]->setVisible(true);
                       players[3]->setPos(19*40,12*40);
           case 3:
                       players[2]->setVisible(true);
                       players[2]->setPos(0*40,12*40);
           case 2:
                       players[1]->setVisible(true);
                       players[1]->setPos(19*40,0*40);
           default:
                       players[0]->setVisible(true);
                       players[0]->setPos(0*40,0*40);
               break;
           }
    }else{
        ungrabKeyboard();
        for(uchar i = 0; i < bombs.length(); i++){
            delete bombs[i];
        }
        bombs.clear();
        for(uchar i = 0; i < bonuses.length(); i++){
            delete bonuses[i];
        }
        bonuses.clear();
        for(uchar i = 0; i < 20; i++){
            for(uchar j = 0; j < 13; j++){
                burning[i][j] = 42;
            }
        }

    }
}

void GraphicsMap::deleteBomb(uchar x, uchar y)
{
    for(uchar i = 0; i < bombs.length(); i++){
        if(
                (bombs[i]->x())/40 == x &&
                (bombs[i]->y())/40 == y
        ){
            delete bombs[i];
            bombs.removeAt(i);
            emit bombBlasted();
            return;
        }
    }
}

void GraphicsMap::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up:
        gameGlobal->InputCommandFromGui(FEL);
        break;
    case Qt::Key_Down:
        gameGlobal->InputCommandFromGui(LE);
        break;
    case Qt::Key_Left:
        gameGlobal->InputCommandFromGui(BALRA);
        break;
    case Qt::Key_Right:
        gameGlobal->InputCommandFromGui(JOBBRA);
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        gameGlobal->InputCommandFromGui(255);
        break;
    }
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
    painter->drawText(QRectF(45, 0, 200, 66).translated(4,4), QString::number(secs/60) + ":" + QString::number(secs%60), QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(45, 0, 200, 66), QString::number(secs/60) + ":" + QString::number(secs%60), QTextOption(Qt::AlignCenter));

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




GraphicsCup::GraphicsCup()
{
    c = gameGlobal->GetCup();
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

void GraphicsCup::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->drawImage(-400, -300, bgnd);
    painter->setFont(font);
    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-300, -300, 600, 66).translated(4,4),
                      (gameGlobal->IsSurvive())?(tr("Survival cup")):(tr("Murder cup")),
                      QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-300, -300, 600, 66),
                      (gameGlobal->IsSurvive())?(tr("Survival cup")):(tr("Murder cup")),
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


































































