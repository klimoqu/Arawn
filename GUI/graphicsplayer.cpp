#include "graphicsplayer.hpp"

GraphicsPlayer::GraphicsPlayer(PlayerImage p, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    aState = 0;
    dir = 2;
    QImage img;
    if(p == TUX){
        img = QImage("res/tux.png");
        big = true;
    }
    if(p == BSD){
        img = QImage("res/bsd.png");
        big = true;
    }
    if(p == SPIDER){
        img = QImage("res/spider.png");
        big = false;
    }
    if(p == SNAKE){
        img = QImage("res/snake.png");
        big = true;
    }
    for(uchar i = 0; i < 10; i++){
        for(uchar j = 0; j < 4; j++){
            if(big)
                pix[i][j] = new QImage(img.copy(i*40, j*60, 40, 60));
            else
                pix[i][j] = new QImage(img.copy(i*40, j*40, 40, 40));
        }
    }

}

QRectF GraphicsPlayer::boundingRect() const
{
    return big ? QRectF(-20, -40, 40, 60) : QRectF(-20, -20, 40, 40);
}

void GraphicsPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(boundingRect(), *( pix[aState][dir]));
}

void GraphicsPlayer::setDir(uchar d)
{
    dir = d;
}


GraphicsBomb::GraphicsBomb(GraphicsPlayer::PlayerImage p, QGraphicsItem *parent)
{
    aState = 0;
    QImage img("res/bombs.png");
    for(uchar i = 0; i < 4; i++){
        if(p == GraphicsPlayer::TUX){
            pix [i] = new QImage(img.copy(160+i*40, 0, 40, 40));
        }
        if(p == GraphicsPlayer::BSD){
            pix [i] = new QImage(img.copy(160+i*40, 40, 40, 40));
        }
        if(p == GraphicsPlayer::SPIDER){
            pix [i] = new QImage(img.copy(i*40, 40, 40, 40));
        }
        if(p == GraphicsPlayer::SNAKE){
            pix [i] = new QImage(img.copy(i*40, 0, 40, 40));
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
