#ifndef GRAPHICSPLAYER_HPP
#define GRAPHICSPLAYER_HPP

#include <QtGui>

class GraphicsPlayer : public QGraphicsItem
{
public:
    GraphicsPlayer(uchar id, QGraphicsItem *parent);

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
private:
    QImage* pix[10][4];
    uchar dir;
};

class GraphicsBomb : public QGraphicsItem
{
public:
    GraphicsBomb(uchar id, QGraphicsItem *parent);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    inline void incAState();

private:
    QImage bombs;
    QImage* pix[4];
    uchar aState;
};

class GraphicsBonus : public QGraphicsItem
{
public:
    GraphicsBonus(uchar type, int xcoord, int ycoord, QGraphicsItem *parent);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QImage *pix;
};



#endif // GRAPHICSPLAYER_HPP
