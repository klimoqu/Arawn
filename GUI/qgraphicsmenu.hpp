#ifndef QGRAPHICSMENU_HPP
#define QGRAPHICSMENU_HPP

#include "arawnheader.h"


class MenuItem
{
public:
    MenuItem(QString &name);
    inline QString name() const;
protected:
    QString itemName;
};

class OptionItem : public MenuItem
{
public:
    explicit OptionItem(QString &name, QVariant &variant, QVariantMap &valuesList);

    bool next();
    bool prev();
    inline QString selected() const;

private:
    QVariant target;
    QVariantMap values;
    uchar sel;
    QStringList keys;
};



class GraphicsMenu : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsMenu(QString &title, QGraphicsObject *parent = 0);

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
    QList<MenuItem *> itemlist;
};

#endif // QGRAPHICSMENU_HPP
