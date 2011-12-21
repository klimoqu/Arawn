#include "qgraphicsmenu.hpp"

OptionItem::OptionItem(QVariant &variant, QList<QPair<QString, QVariant> > &valuesList):
    target(variant), values(valuesList)
{
    selected = values.indexOf(QPair<QString, QVariant>());

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


