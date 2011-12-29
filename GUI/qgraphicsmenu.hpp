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
    void menuChanged();

public slots:
    void keyDown();
    void keyUp();
    void keyLeft();
    void keyRight();
    void keyEnter();

private:

    QString tit;
    char selected;
    uchar sum;
    MenuList menus;
    OptionList options;
    QFont titFont;
    QFont itemFont;
};


class GraphicsAbout : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsAbout();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString h1;
    QString h2;
    QString p1;
    QFont h1Font;
    QFont h2Font;
    QFont p1Font;
};

#endif // QGRAPHICSMENU_HPP
