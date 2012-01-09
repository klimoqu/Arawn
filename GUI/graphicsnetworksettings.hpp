#ifndef GRAPHICSNETWORKSETTINGS_HPP
#define GRAPHICSNETWORKSETTINGS_HPP
#include <QtGui>

class GraphicsNetworkSettings : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsNetworkSettings(QAbstractState *_backState, QState *_ownState, QState *_nextState);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void connectionClosing();
    void previousState();
    void startConnecting();

public slots:
    void setGrabKeyboard();
    void setUnGrabKeyboard();
    void connectionFail();

private:
    void keyPressEvent(QKeyEvent *event);

    QString title;
    QString text;
    QVariant lineEdit;
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
