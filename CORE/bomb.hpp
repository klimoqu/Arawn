#pragma once
#include <QObject>
#include <QTimer>

class Bomb : public QObject
{
    Q_OBJECT
    uchar x,y;
    uchar size,id;
    QTimer qt;
    bool canfail;
public:
    Bomb(uchar x, uchar y, uchar size, uchar id,int timeout,bool canfail)
    {
        this->id=id;
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
    void Boomed(uchar x, uchar y,uchar size,uchar id,uchar direction);
    void DeleteThis(Bomb* b);
public slots:
    void Boom()
    {
        canfail?emit Boomed(255,255,0,id,255):emit Boomed(this->x,this->y,this->size,id,255);
        emit DeleteThis(this);
    }
    void Boom(uchar x, uchar y)
    {
        if(this->x==x && this->y==y)Boom();
    }
};
