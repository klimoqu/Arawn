#include "qgraphicsmenu.hpp"

QGraphicsMenu::QGraphicsMenu(QString &title, QObject *parent)
    : QObject(parent), title(title)
{
}

void QGraphicsMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

QPainterPath QGraphicsMenu::shape() const
{
}

QRectF QGraphicsMenu::boundingRect() const
{
}

void QGraphicsMenu::addMenuItem(MenuItem *item)
{
}

void QGraphicsMenu::addOptionItem(OptionItem *item)
{
}

void QGraphicsMenu::keyPressEvent(QKeyEvent *event)
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


MenuItem::MenuItem(QString &name, QState *sourceState, QState *destinationState)
{
    this->itemName = name;
    this->sourceState = sourceState;
    this->destinationState = destinationState;
}


