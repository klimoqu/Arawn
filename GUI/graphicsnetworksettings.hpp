#ifndef GRAPHICSNETWORKSETTINGS_HPP
#define GRAPHICSNETWORKSETTINGS_HPP
#include <QtGui>
#include "CORE/game.hpp"

class GraphicsNetworkSettings : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsNetworkSettings(QAbstractState *_backState, QState *_ownState, QState *_nextState);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void previousState();
    void connectionOk();

public slots:
    void setGrabKeyboard();
    void setUnGrabKeyboard();
    void connectionFail();

private:
    void keyPressEvent(QKeyEvent *event);

    Game *g;
    QString title;
    QString text;
    QString connectText;
    QString connecting;
    QAbstractState *backState;
    QState *ownState;
    QState *nextState;
    QFont titFont;
    QFont itemFont;
    QFont lineFont;
    char selected; //0: sorszerkesztő, 1: gomb, 2: várakozás(csak esc)
};



#endif // GRAPHICSNETWORKSETTINGS_HPP
