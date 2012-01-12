#ifndef GRAPHICSNETWORKSETTINGS_HPP
#define GRAPHICSNETWORKSETTINGS_HPP
#include <QtGui>
#include "CORE/game.hpp"

class GraphicsNetworkSettings : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsNetworkSettings(Game *_g, QAbstractState *_backState, QState *_ownState, QState *_roomState, QState *_gameState);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void previousState();
    void trNextState();

public slots:
    void setGrabKeyboard();
    void setUnGrabKeyboard();
    void connectionFail();
    void connectionOk();

private:
    void keyPressEvent(QKeyEvent *event);

    QState *gameState;
    QState *roomState;
    Game *g;
    QString title;
    QString text;
    QString connectText;
    QString connecting;
    QFont titFont;
    QFont itemFont;
    QFont lineFont;
    char selected; //0: sorszerkesztő, 1: gomb, 2: várakozás(csak esc)
};



#endif // GRAPHICSNETWORKSETTINGS_HPP
