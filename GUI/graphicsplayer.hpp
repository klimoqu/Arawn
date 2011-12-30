#ifndef GRAPHICSPLAYER_HPP
#define GRAPHICSPLAYER_HPP

#include "arawnheader.h"

class GraphicsPlayer : public QGraphicsItem
{
    enum PlayerImage{
        TUX, BSD, SPIDER, SNAKE
    };

public:
    GraphicsPlayer(PlayerImage p, QGraphicsItem *parent);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QImage* pix[10][4];
};

#endif // GRAPHICSPLAYER_HPP
