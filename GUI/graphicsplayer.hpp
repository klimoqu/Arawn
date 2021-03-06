#ifndef GRAPHICSPLAYER_HPP
#define GRAPHICSPLAYER_HPP

#include <QtGui>

class GraphicsPlayer : public QGraphicsItem
{
public:
    GraphicsPlayer(uchar id, QGraphicsItem *parent);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void setDir(uchar d)
    {
        dir = d;
    }

    inline void incAState()
    {
        if(aState == 9) return;
        if(aState < 8) aState++;
        else aState = 0;
    }

    uchar aState;
private:
    QImage* pix[10][4];
    uchar dir;
};


class GraphicsBomb : public QGraphicsItem
{
public:
    GraphicsBomb(uchar x, uchar y, uchar p, QGraphicsItem *parent);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void incAState(){
        if(aState < 3) aState++;
        else aState = 0;
    }

private:
    QImage* pix[4];
    uchar aState;
};

class GraphicsBonus : public QGraphicsItem
{
public:
    GraphicsBonus(uchar type, uchar x, uchar y, QGraphicsItem *parent);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QImage *pix;
};



#endif // GRAPHICSPLAYER_HPP
