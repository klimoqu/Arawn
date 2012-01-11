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
    QFont titFont;
    QFont itemFont;
};

#endif // GRAPHICSNETWORKROOM_HPP
