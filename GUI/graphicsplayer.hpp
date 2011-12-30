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
    inline void incAState();

private:
    QImage* pix[10][4];
    bool big;
    uchar aState;
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
