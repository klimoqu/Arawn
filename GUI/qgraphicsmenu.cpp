#include "arawnheader.h"


MenuItem::MenuItem(const QString &name) : itemName(name){}

QString MenuItem::name() const
{
    return itemName;
}




OptionItem::OptionItem(const QString &name, QVariant &variant, QVariantMap &valuesMap):
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




GraphicsMenu::GraphicsMenu(const QString &title, QGraphicsItem *par):
    QGraphicsObject(par)
{
    tit = title;
    selected = 0;
    sum = 0;
}

void GraphicsMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    //Kistéglalap a kijelöléshez
    painter->setBrush(QColor(150,100,150,100));
    painter->setPen(Qt::NoPen);
    painter->drawRect(-225, selected*50-(sum*25), 450, 50);


    //Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-225,-(sum*25 + 113), 450, 75).translated(4,4), tit, QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-225,-(sum*25 + 113), 450, 75), tit, QTextOption(Qt::AlignCenter));

    //Elemek
    short i = 0;
    foreach (MenuItem m, menus) {
        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(-225, i*50-(sum*25), 450, 50).translated(4,4), m.name(), QTextOption(Qt::AlignCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-225, i*50-(sum*25), 450, 50), m.name(), QTextOption(Qt::AlignCenter));
        i++;
    }
    foreach (OptionItem o, options){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(-225, i*50-(sum*25), 450, 50).translated(4,4), o.name(), QTextOption(Qt::AlignLeft));
        painter->drawText(QRectF(-225, i*50-(sum*25), 450, 50).translated(4,4), o.selected(), QTextOption(Qt::AlignRight));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-225, i*50-(sum*25), 450, 50), o.name(), QTextOption(Qt::AlignLeft));
        painter->drawText(QRectF(-225, i*50-(sum*25), 450, 50), o.selected(), QTextOption(Qt::AlignRight));
        i++;
    }

    painter->restore();
}

QRectF GraphicsMenu::boundingRect() const
{
    return QRectF(-150,-(sum*25 + 113),300,88+sum*50);
}

void GraphicsMenu::addMenuItem(const QString &name)
{
    menus.push_back(MenuItem(name));
    sum++;
}

void GraphicsMenu::addOptionItem(const QString &name, QVariant &variant, QVariantMap &vmap)
{
    options.push_back(OptionItem(name, variant, vmap));
    sum++;
}

void GraphicsMenu::keyPress(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        emit escapePushed();
        return;
    }
    if(event->key() == Qt::Key_Down){
        if(selected >= sum) return;
        selected++;
        //update(-150, (selected-1)*50-(sum*25), 300, 100);
        updateMicroFocus();
        return;
    }
    if(event->key() == Qt::Key_Up){
        if(selected == 0) return;
        selected--;
        //update(-150, selected*50-(sum*25), 300, 100);
        updateMicroFocus();
        return;
    }
    if(event->key() == Qt::Key_Left){
        if(selected < menus.size()) return;
        options[selected-menus.size()].prev();
        update(-150, selected*50-(sum*25), 300, 50);
        return;
    }
    if(event->key() == Qt::Key_Right){
        if(selected < menus.size()) return;
        options[selected-menus.size()].next();
        update(-150, selected*50-(sum*25), 300, 50);
        return;
    }
    if(event->key() == Qt::Key_Enter ||
       event->key() == Qt::Key_Return){
        if(selected >= menus.size()) return;
        switch(selected){
        case 0:
            emit menu1Selected();
            break;
        case 1:
            emit menu2Selected();
            break;
        case 2:
            emit menu3Selected();
            break;
        case 3:
            emit menu4Selected();
            break;
        case 4:
            emit menu5Selected();
            break;
        case 5:
            emit menu6Selected();
            break;
        case 6:
            emit menu7Selected();
            break;
        }
    }
}

