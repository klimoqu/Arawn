#ifndef QGRAPHICSMENU_HPP
#define QGRAPHICSMENU_HPP

#include "arawnheader.h"

class MenuItem
{
public:
    inline MenuItem(const QString &name);
    inline QString name() const;
protected:
    QString itemName;
};

class OptionItem
{
public:
    explicit OptionItem(const QString &name, QVariant &variant, QVariantMap &valuesList);

    bool next();
    bool prev();
    inline QString selected() const;
    inline QString name() const;
private:
    QString itemName;
    QVariant target;
    QVariantMap values;
    uchar sel;
    QStringList keys;
};


typedef QList<MenuItem> MenuList;
typedef QList<OptionItem> OptionList;

class GraphicsMenu : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsMenu(const QString &title, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    void addMenuItem(const QString &name);
    void addOptionItem(const QString &name, QVariant &variant, QVariantMap &vmap);


signals:
    void menu1Selected();
    void menu2Selected();
    void menu3Selected();
    void menu4Selected();
    void menu5Selected();
    void menu6Selected();
    void menu7Selected();
    void escapePushed();

private:
    void keyPressEvent(QKeyEvent *event);

    QString tit;
    char selected;
    uchar sum;
    MenuList menus;
    OptionList options;
};

#endif // QGRAPHICSMENU_HPP
