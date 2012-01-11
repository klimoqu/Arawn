#ifndef GRAPHICSNETWORKROOM_HPP
#define GRAPHICSNETWORKROOM_HPP
#include <QtGui>
#include "CORE/game.hpp"

class GraphicsNetworkRoom : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsNetworkRoom();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setParams(Game *_g, QState *_ownState, QState *_gameState);

protected slots:
    void pushPlayer();

private:

    Game *g;
    QString playerStrs[4];
    QString playerNames[4];
    uchar playerNums; // 0,1,2,3
    QFont titFont;
    QFont itemFont;
    QFont nameFont;
};

#endif // GRAPHICSNETWORKROOM_HPP
