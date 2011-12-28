#pragma once
#include <QObject>
#include <QTimer>

class Bomb : QObject
{
    Q_OBJECT
    float x,y;
    uchar size;
    QTimer qt;
public:
    Bomb(float x, float y, uchar size, int timeout)
    {
        this->x=x;
        this->y=y;
        this->size=size;
        qt.setSingleShot(true);
        qt.start(timeout);
        connect(&qt,SIGNAL(timeout()), this, SLOT(Boom()));
    }
signals:
    void Planted(float x, float y);
    void Boomed(float x, float y,uchar size,uchar direction);
    void DeleteThis(Bomb* b);
public slots:
    void Boom()
    {
        emit Boomed(this->x,this->y,this->size,0);
        emit DeleteThis(this);
    }
    void Boom(float x, float y, uchar size, uchar diretion)
    {
        if(this->x==x && this->y==y)Boom();
    }
};
