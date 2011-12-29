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
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(38);
}

void GraphicsMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    //Kistéglalap a kijelöléshez
    painter->setBrush(QColor(150,100,150,100));
    painter->setPen(Qt::NoPen);
    painter->drawRect(-240, selected*50-(sum*25), 480, 50);


    //Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    painter->drawText(QRectF(-240,-(sum*25 + 113), 480, 75).translated(4,4), tit, QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-240,-(sum*25 + 113), 480, 75), tit, QTextOption(Qt::AlignCenter));

    //Elemek
    painter->setFont(itemFont);
    short i = 0;
    foreach (MenuItem m, menus) {
        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(-240, i*50-(sum*25), 480, 50).translated(4,4), m.name(), QTextOption(Qt::AlignCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-240, i*50-(sum*25), 480, 50), m.name(), QTextOption(Qt::AlignCenter));
        i++;
    }
    foreach (OptionItem o, options){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(-238, i*50-(sum*25), 473, 50).translated(4,4), o.name(), QTextOption(Qt::AlignLeft));
        painter->drawText(QRectF(-238, i*50-(sum*25), 473, 50).translated(4,4), o.selected(), QTextOption(Qt::AlignRight));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-238, i*50-(sum*25), 473, 50), o.name(), QTextOption(Qt::AlignLeft));
        painter->drawText(QRectF(-238, i*50-(sum*25), 473, 50), o.selected(), QTextOption(Qt::AlignRight));
        i++;
    }

    painter->restore();
}

QRectF GraphicsMenu::boundingRect() const
{
    return QRectF(-240,-(sum*25 + 113),480,117+sum*50);
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

void GraphicsMenu::keyDown()
{
    if(selected >= sum-1) return;
    selected++;
    emit menuChanged();
    update(-225, (selected-1)*50-(sum*25), 450, 100);
    return;
}

void GraphicsMenu::keyUp()
{
    if(selected == 0) return;
    selected--;
    emit menuChanged();
    update(-225, selected*50-(sum*25), 450, 100);
    return;
}

void GraphicsMenu::keyLeft()
{
    if(selected < menus.size()) return;
    if(options[selected-menus.size()].prev())
        emit menuChanged();
    update(-225, selected*50-(sum*25), 450, 50);
    return;
}

void GraphicsMenu::keyRight()
{
    if(selected < menus.size()) return;
    if(options[selected-menus.size()].next())
        emit menuChanged();
    update(-225, selected*50-(sum*25), 450, 50);
    return;
}

void GraphicsMenu::keyEnter()
{
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




GraphicsAbout::GraphicsAbout()
{
    h1 = tr("Credits");
    h2 = "Hir yw'r dydd a hir yw'r nos, a hir yw aros Arawn";
    p1 = "This is a bomberman like game inspired by the well known ClanBomber.\nIt is written in Qt by Moreh Tamas, Klicsu Zsolt and Quintz Gabor in 2011.";
    h1Font = qApp->font();
    h1Font.setPixelSize(50);
    h2Font = qApp->font();
    h2Font.setPixelSize(40);
    p1Font = qApp->font();
    p1Font.setPixelSize(30);
}

QRectF GraphicsAbout::boundingRect() const
{
    return QRectF(-300, -275, 600, 550);
}

void GraphicsAbout::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    // Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(h1Font);
    painter->drawText(QRectF(-300,-275, 600, 75).translated(4,4), h1, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-300,-275, 600, 75), h1, QTextOption(Qt::AlignCenter | Qt::AlignTop));

    // Alcím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(h2Font);
    painter->drawText(QRectF(-300,-190, 600, 125).translated(3,3), h2, QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-300,-190, 600, 125), h2, QTextOption(Qt::AlignCenter));

    //Szöveg
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(p1Font);
    painter->drawText(QRectF(-290,-65, 580, 340).translated(2,2), p1, QTextOption(Qt::AlignTop | Qt::AlignLeading));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-290,-65, 580, 340), p1, QTextOption(Qt::AlignTop | Qt::AlignLeading));

    painter->restore();
}

