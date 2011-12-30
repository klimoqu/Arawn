#ifndef GRAPHICSPLAYER_HPP
#define GRAPHICSPLAYER_HPP

#include "arawnheader.h"

class GraphicsPlayer : public QGraphicsItem
{
public:
    enum PlayerImage{
        TUX, BSD, SPIDER, SNAKE
    };

    GraphicsPlayer(PlayerImage p, QGraphicsItem *parent);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void setDir(uchar d);
    inline void incAState()
    {
        if(aState == 9) return;
        if(aState < 8) aState++;
        else aState = 0;
    }

    uchar aState;
    PlayerImage img;
private:
    QImage* pix[10][4];
    bool big;
    uchar dir;
};

class GraphicsBomb : public QGraphicsItem
{

public:
    GraphicsBomb(GraphicsPlayer::PlayerImage p, QGraphicsItem *parent);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void incAState();

private:
    QImage* pix[4];
    uchar aState;
};




#endif // GRAPHICSPLAYER_HPP
