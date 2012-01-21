#pragma once
#include <QObject>
#include <QtCore>
#include <QTimer>

class Bomb : public QObject
{
    Q_OBJECT
    uchar x,y;
    uchar size,id;
    QTimer qt;
    bool canfail,boomed;
public:
    Bomb(uchar x, uchar y, uchar size, uchar id,int timeout,bool canfail)
    {
        this->id=id;
        this->canfail=canfail;
        this->x=x;
        this->y=y;
        this->size=size;
		boomed=false;
		QTimer::singleShot(timeout*100, this, SLOT(Boom()));
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
		boomed=true;
    }
    void Boom(uchar x, uchar y,uchar size,uchar id,uchar direction)
    {
        if(this->x==x && this->y==y && !boomed)Boom();
		emit DeleteThis(this);
    }
};
