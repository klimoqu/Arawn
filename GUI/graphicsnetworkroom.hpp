#ifndef GRAPHICSNETWORKROOM_HPP
#define GRAPHICSNETWORKROOM_HPP
#include <QtGui>
#include "../CORE/game.hpp"

class GraphicsNetworkRoom : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsNetworkRoom();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void setParams(QState *_ownState, QState *_gameState);

protected slots:
    void pushPlayer();

private:

    QString playerStrs[4];
    QString playerNames[4];
    uchar playerNums; // 0,1,2,3
    QFont titFont;
    QFont itemFont;
    QFont nameFont;


};

#endif // GRAPHICSNETWORKROOM_HPP
