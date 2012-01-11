#ifndef GRAPHICSNETWORKROOM_HPP
#define GRAPHICSNETWORKROOM_HPP
#include <QtGui>
#include "CORE/game.hpp"

class GraphicsNetworkRoom : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsNetworkRoom(Game *_g, QState *_ownState, QState *_gameState);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void startGame();
public slots:
    void setGrabKeyboard();
    void setUnGrabKeyboard();

private:
    void keyPressEvent(QKeyEvent *event);

    Game *g;
    QString title;
    QString playerStrs[4];
    QString playerNames[4];
    uchar playerNums;
    QFont titFont;
    QFont itemFont;
};

#endif // GRAPHICSNETWORKROOM_HPP
