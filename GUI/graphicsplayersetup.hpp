#ifndef GRAPHICSPLAYERSETUP_HPP
#define GRAPHICSPLAYERSETUP_HPP

#include <QtGui>

class GraphicsPlayerSetup : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsPlayerSetup() {}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString title;
    QString humanPlayer;
    QString cpu1Player;
    QString cpu2Player;
    QString cpu3Player;
    QString hPlayerName;
    QString c1PlayerName;
    QString c2PlayerName;
    QString c3PlayerName;
};

#endif // GRAPHICSPLAYERSETUP_HPP
