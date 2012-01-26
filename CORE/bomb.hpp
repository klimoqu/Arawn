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
    bool canfail;
public:
    Bomb(uchar x, uchar y, uchar size, uchar id,int timeout,bool canfail)
    {
        this->id=id;
        this->canfail=canfail;
        this->x=x;
        this->y=y;
        this->size=size;
		QTimer::singleShot(timeout*100, this, SLOT(Boom()));
    }
    uchar GetX()const
    {
        return x;
    }
    uchar GetY()const
    {
        return y;
    }
    uchar GetSize()const
    {
        return size;
    }
signals:
    void Planted(uchar x, uchar y);
    void Boomed(uchar x, uchar y,uchar size,uchar id,uchar direction);
	void Failed(uchar x, uchar y);
    void DeleteThis(Bomb* b);
public slots:
    void Boom()
    {
		if(canfail)
		{
			emit Failed(this->x,this->y);
			emit Boomed(255,255,0,this->id,255);
		}
		else
		{
			emit Boomed(this->x,this->y,this->size,id,255);
		}
		emit DeleteThis(this);
    }
    void Boom(uchar x, uchar y,uchar size,uchar id,uchar direction)
    {
        if(this->x==x && this->y==y)Boom();
    }
};
