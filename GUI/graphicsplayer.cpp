#include "graphicsplayer.hpp"

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
        for(uchar j = 0; j < 4; j++){
            pix[i][j] = new QImage(img.copy(i*40, j*60, 40, 60));
        }
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


GraphicsBomb::GraphicsBomb(uchar p, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    QImage bombsF("res/bombs.png");
    aState = 0;
    for(uchar i = 0; i < 4; i++){
        if(p == 0){
            pix [i] = new QImage(bombsF.copy(i*40, 0, 40, 40));
            return;
        }
        if(p == 1){
            pix [i] = new QImage(bombsF.copy(i*40, 40, 40, 40));
            return;
        }
        if(p == 2){
            pix [i] = new QImage(bombsF.copy(i*40, 80, 40, 40));
            return;
        }
        if(p == 3){
            pix [i] = new QImage(bombsF.copy(i*40, 120, 40, 40));
            return;
        }
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

GraphicsBonus::GraphicsBonus(uchar type, int xcoord, int ycoord, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    QImage extrasF("res/extras.png");
    setPos(xcoord, ycoord);
    switch(type){
    case 1:
        pix = new QImage(extrasF.copy(40, 0, 40, 40));
        return;
    case 2:
        pix = new QImage(extrasF.copy(360, 0, 40, 40));
        return;
    case 3:
        pix = new QImage(extrasF.copy(0, 0, 40, 40));
        return;
    case 4:
        pix = new QImage(extrasF.copy(320, 0, 40, 40));
        return;
    case 5:
        pix = new QImage(extrasF.copy(80, 0, 40, 40));
        return;
    case 6:
        pix = new QImage(extrasF.copy(400, 0, 40, 40));
        return;
    case 7:
        pix = new QImage(extrasF.copy(280, 0, 40, 40));
        return;
    case 8:
        pix = new QImage(extrasF.copy(240, 0, 40, 40));
        return;
    case 9:
        pix = new QImage(extrasF.copy(200, 0, 40, 40));
        return;
    }
}

QRectF GraphicsBonus::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

void GraphicsBonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(0, 0, *pix);
}
























