#ifndef QGRAPHICSMENU_HPP
#define QGRAPHICSMENU_HPP

#include "arawnheader.h"

class AbstractItem
{
protected:
    QString itemName;
    virtual void doIt() = 0;
};

class MenuItem : public AbstractItem
{
public:
    MenuItem(QString &name, QState *sourceState, QState *destinationState);

private:
    void doIt();
    QState *destinationState;
    QState *sourceState;
};

class OptionItem : public AbstractItem
{
public:
    OptionItem();

private:
    void doIt();
    QVariant target;
    QList<QPair<QString, QVariant> > values;
};



class QGraphicsMenu : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit QGraphicsMenu(QString &title, QObject *parent = 0);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    void addMenuItem(QString &name, QState *destination);
    //void addOptionItem(QString &name, );

    void addMenuItem(MenuItem *item);
    void addOptionItem(OptionItem *item);

signals:
    void menu1Selected();
    void menu2Selected();
    void menu3Selected();
    void menu4Selected();
    void menu5Selected();
    void menu6Selected();
    void menu7Selected();
    void escapePushed();

public slots:

private:
    void keyPressEvent(QKeyEvent *event);

    QString title;
    uchar selected;
    QList<AbstractItem *> itemlist;
};

#endif // QGRAPHICSMENU_HPP
