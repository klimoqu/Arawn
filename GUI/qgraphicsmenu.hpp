#ifndef QGRAPHICSMENU_HPP
#define QGRAPHICSMENU_HPP

#include <QtGui>


class QArawnWindow;

/// StatedItemObject: Az (al)menü és menüelem absztrakt osztálya
class StatedItemObject
{
public:
    QString title;
    QState *myState;
};



/// MenuItem: Menübejegyzés, melyből egy másik state hívható
class MenuItem : public StatedItemObject
{
public:
    inline MenuItem(const QString &title, QState *targetState)
    {
        this->title = title;
        this->myState = targetState;
    }
};



/// OptionItem: primitív struct, elemek közti váltásra alkalmas
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
    QVariant *target;
    QVariantMap *values;
    uchar sel;
    QStringList keys;
};



/// GraphicsMenu: menü és/vagy almenü
class GraphicsMenu : public QGraphicsObject, public StatedItemObject
{
    Q_OBJECT
public:
    GraphicsMenu(const QString &title, QState *parentState, QState *ownState, QSound *menuStep, QSound *stepInto, QArawnWindow *window);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);


    GraphicsMenu* addSubMenu(const QString &name);
    void addOptionItem(const QString &name, QVariant &variant, QVariantMap &vmap);
    void addMenuItem(const QString &title, QState *targetState);

    void setMenuStepSound(QSound *sound);
    void setIntoSound(QSound *sound);

signals:
    void menu1Selected();
    void menu2Selected();
    void menu3Selected();
    void menu4Selected();
    void menu5Selected();
    void menu6Selected();
    void menu7Selected();

public slots:
    void keyDown();
    void keyUp();
    void keyLeft();
    void keyRight();
    void keyEnter();

private:
    char selected;
    uchar sum;
    QList<StatedItemObject> menus;
    QList<OptionItem> options;
    QFont titFont;
    QFont itemFont;
    QState *parentState;
    QSound *menuStep;
    QSound *stepInto;
    QArawnWindow *win;
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
