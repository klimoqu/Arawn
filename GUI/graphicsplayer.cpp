#include "graphicsplayer.hpp"
#include "imagefactory.hpp"

#define LE 2
#define FEL 1
#define JOBBRA 3
#define BALRA 0
#define MINDEN 255

GraphicsPlayer::GraphicsPlayer(uchar p, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    aState = 0;
    dir = 2;
    QImage img;
    if(p == 0){
        img = QImage("res/a_red.png");
    }
    if(p == 1){
        img = QImage("res/a_green.png");
    }
    if(p == 2){
        img = QImage("res/a_blue.png");
    }
    if(p == 3){
        img = QImage("res/a_yellow.png");
    }
    for(uchar i = 0; i < 10; i++){
        pix[i][2] = new QImage(img.copy(i*40, 0, 40, 60));
        pix[i][1] = new QImage(img.copy(i*40, 120, 40, 60));
        pix[i][3] = new QImage(img.copy(i*40, 180, 40, 60));
        pix[i][0] = new QImage(img.copy(i*40, 60, 40, 60));
    }

}

QRectF GraphicsPlayer::boundingRect() const
{
    return QRectF(0, -20, 40, 60);
}

void GraphicsPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(boundingRect(), *( pix[aState][dir]));
}


GraphicsBomb::GraphicsBomb(uchar x, uchar y, uchar p, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setPos(x*40, y*40);
    aState = 0;
    for(uchar i = 0; i < 4; i++){
       pix[i] = imgFact->bombImages[p][i];
    }

}

QRectF GraphicsBomb::boundingRect() const
{
    return QRectF(0,0,40,40);
}

void GraphicsBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(), *(pix[aState]));
}

void GraphicsBomb::incAState()
{
    if(aState < 3) aState++;
    else aState = 0;
}

GraphicsBonus::GraphicsBonus(uchar type, uchar x, uchar y, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    setPos(x*40, y*40);
    pix = imgFact->bonusImages[type-1];
}

QRectF GraphicsBonus::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

void GraphicsBonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, 0, *pix);
}
























