#include "qgraphicsmenu.hpp"

OptionItem::OptionItem(QString &name, QVariant &variant, QVariantMap &valuesList):
    target(variant), values(valuesList), itemName(name)
{
    keys = values.keys();
    sel = 0;
    foreach (k, keys) {
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



//GraphicsMenu::GraphicsMenu(QString &title, QGraphicsObject *parent)
//    : QGraphicsObject(parent), title(title)
//{
//}

//void GraphicsMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//}

//QPainterPath GraphicsMenu::shape() const
//{
//}

//QRectF GraphicsMenu::boundingRect() const
//{
//}

//void GraphicsMenu::addMenuItem(MenuItem *item)
//{
//}

//void GraphicsMenu::addOptionItem(OptionItem *item)
//{
//}

//void GraphicsMenu::keyPressEvent(QKeyEvent *event)
//{
//    if(event->key() == Qt::Key_Escape){
//        emit escapePushed();
//        return;
//    }
//    if(event->key() == Qt::Key_Down){

//    }
//    if(event->key() == Qt::Key_Up){

//    }
//    if(event->key() == Qt::Key_Left){

//    }
//    if(event->key() == Qt::Key_Right){

//    }
//    if(event->key() == Qt::Key_Enter ||
//       event->key() == Qt::Key_Return){

//    }
//}


//MenuItem::MenuItem(QString &name, QState *sourceState, QState *destinationState)
//{
//    this->itemName = name;
//    this->sourceState = sourceState;
//    this->destinationState = destinationState;
//}


