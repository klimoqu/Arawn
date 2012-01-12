#include "GUI/graphicsmap.hpp"

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
    GraphicsBomb *bomb = new GraphicsBomb(players[player]->img, this);
    bomb->setX(x*40);
    bomb->setY(y*40);
    emit bombPlanted();
    bombs.append(bomb);
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
}

void GraphicsMap::blastingOut(uchar x, uchar y)
{
    burning[x][y] += 50;
}

void GraphicsMap::changeField(uchar x, uchar y, uchar type)
{
    mapIDs[x][y] = type;
}

void GraphicsMap::movePlayer(uchar player, uchar dir)
{
    players[player]->incAState();
    switch(dir){
    case BALRA:
        players[player]->setX(players[player]->x()-8);
        return;
    case FEL:
        players[player]->setY(players[player]->y()-8);
        return;
    case LE:
        players[player]->setY(players[player]->y()+8);
        return;
    case JOBBRA:
        players[player]->setX(players[player]->x()+8);
        return;
    default:
        return;
    }
}

void GraphicsMap::diePlayer(uchar player)
{
    emit playerDied();
    players[player]->aState = 9;
}

void GraphicsMap::blastPlayer(uchar player)
{
    players[player]->setVisible(false);
    emit playerBlasted();
}

void GraphicsMap::setMapIDs()
{
    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            mapIDs[i][j] = g->GetFields()[i][j];
        }
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
























