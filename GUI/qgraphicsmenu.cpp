#include "qgraphicsmenu.hpp"


MenuItem::MenuItem(QString &name) : itemName(name){}

QString MenuItem::name() const
{
    return itemName;
}



OptionItem::OptionItem(QString &name, QVariant &variant, QVariantMap &valuesMap):
    itemName(name), target(variant), values(valuesMap)
{
    keys = values.keys();
    sel = 0;
    foreach (QString k, keys) {
        if(values[k] == target)
            break;
        sel++;
    }
}

bool OptionItem::next()
{
    if(sel < (keys.size()-1)){
        sel++;
        target = values[keys[sel]];
        return true;
    }
    return false;
}

bool OptionItem::prev()
{
    if(sel > 0){
        sel--;
        target = values[keys[sel]];
        return true;
    }
    return false;
}

QString OptionItem::selected() const
{
    return keys[sel];
}

QString OptionItem::name() const
{
    return itemName;
}



GraphicsMenu::GraphicsMenu(QString &title, QGraphicsItem *par):
    QGraphicsObject(par)
{
    tit = title;
    selected = 0;
    sum = 0;
}

void GraphicsMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

QRectF GraphicsMenu::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void GraphicsMenu::addMenuItem(QString &name)
{
    menus.push_back(MenuItem(name));
    sum++;
}

void GraphicsMenu::addOptionItem(QString &name, QVariant &variant, QVariantMap &vmap)
{
    options.push_back(OptionItem(name, variant, vmap));
    sum++;
}

void GraphicsMenu::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        emit escapePushed();
        return;
    }
    if(event->key() == Qt::Key_Down){

    }
    if(event->key() == Qt::Key_Up){

    }
    if(event->key() == Qt::Key_Left){

    }
    if(event->key() == Qt::Key_Right){

    }
    if(event->key() == Qt::Key_Enter ||
       event->key() == Qt::Key_Return){

    }
}

void GraphicsMenu::keyReleaseEvent(QKeyEvent *event)
{
}


