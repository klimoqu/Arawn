#include "graphicsmap.hpp"

GraphicsMap::GraphicsMap(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    /// \todo, bImages
    fPixmaps[0] = new QImage("res/field0.png");
    fPixmaps[1] = new QImage("res/field1.png");
    fPixmaps[2] = new QImage("res/field2.png");
    fPixmaps[3] = new QImage("res/field3.png");
    fPixmaps[4] = new QImage(40,40, QImage::Format_Mono);
    fPixmaps[5] = new QImage("res/field5.png");



    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            burning[i][j] = 42;
        }
    }
}

QRectF GraphicsMap::boundingRect() const
{
    return QRectF(0,0,800,520);
}

void GraphicsMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    painter->save();

    // Pálya
    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            painter->drawImage(i*40, j*40, *(fPixmaps[mapIDs[i][j]]));
        }
    }

    // Bombák
    for(uchar i = 0; i < bombs.length(); i++){
        bombs[i]->paint(painter, o, w);
    }

    // Játékosok
    for(uchar i = 0; i < playersCount; i++){
        players[i]->paint(painter, o, w);
    }

    // Tűz
    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            painter->drawImage(i*40, j*40, *(bImages[burning[i][j]]));
        }
    }
    painter->restore();
}

void GraphicsMap::plantBomb(uchar x, uchar y, uchar player)
{
    GraphicsBomb *bomb = new GraphicsBomb(players[player]->img, this);
    bomb->setX(x*40);
    bomb->setY(y*40);
    bombs.append(bomb);
}

void GraphicsMap::blastField(uchar x, uchar y, uchar player, uchar dir)
{
    burning[x][y] = dir;
    /// TODO player
}

void GraphicsMap::blastingOut(uchar x, uchar y)
{
    burning[x][y] += 50;
}

void GraphicsMap::changeField(uchar x, uchar y, uchar type)
{
    mapIDs[x][y] = type;
}

void GraphicsMap::movePlayer(uchar player, uchar dir)
{
    switch(dir){
    case 0:
        players[player]->setX(players[player]->x()-8);
        return;
    case 1:
        players[player]->setY(players[player]->y()-8);
        return;
    case 2:
        players[player]->setY(players[player]->y()+8);
        return;
    case 3:
        players[player]->setX(players[player]->x()+8);
        return;
    default:
        return;
    }
}

void GraphicsMap::diePlayer(uchar player)
{
    players[player]->aState = 9;
}

void GraphicsMap::blastPlayer(uchar player)
{
    players[player]->setVisible(false);
    /// TODO ha látható a vér, rajzoljon ki néhányat
}

void GraphicsMap::setMapIDs(Field **&fields)
{
    for(uchar i = 0; i < 20; i++){
        for(uchar j = 0; j < 13; j++){
            mapIDs[i][j] = fields[i][j].GetType();
        }
    }
}
