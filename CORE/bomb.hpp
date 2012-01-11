#pragma once
#include <QObject>
#include <QTimer>

class Bomb : QObject
{
    Q_OBJECT
    uchar x,y;
    uchar size;
    QTimer qt;
    bool canfail;
public:
    Bomb(uchar x, uchar y, uchar size, int timeout,bool canfail)
    {
        this->canfail=canfail;
        this->x=x;
        this->y=y;
        this->size=size;
        qt.setSingleShot(true);
        qt.start(timeout);
        connect(&qt,SIGNAL(timeout()), this, SLOT(Boom()));
    }
    uchar GetX()
    {
        return x;
    }
    uchar GetY()
    {
        return y;
    }
    uchar GetSize()
    {
        return size;
    }
signals:
    void Planted(uchar x, uchar y);
    void Boomed(uchar x, uchar y,uchar size,uchar direction);
    void DeleteThis(Bomb* b);
public slots:
    void Boom()
    {
        if(!canfail)emit Boomed(this->x,this->y,this->size,0);
        emit DeleteThis(this);
    }
    void Boom(uchar x, uchar y)
    {
        if(this->x==x && this->y==y)Boom();
    }
};
