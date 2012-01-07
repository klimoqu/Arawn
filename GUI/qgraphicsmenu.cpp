#include "GUI/qgraphicsmenu.hpp"
#include "GUI/qarawnwindow.hpp"



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




GraphicsMenu::GraphicsMenu(const QString &_title, QState *_parentState, QState *ownState, QSound *_menuStep, QSound *_stepInto, QArawnWindow *window)
{
    win = window;
    win->scene->addItem(this);
    title = _title;
    selected = 0;
    sum = 0;
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(38);
    menuStep = _menuStep;
    stepInto = _stepInto;
    myState = ownState;
    parentState = _parentState;

    myState->machine()->addDefaultAnimation(new QPropertyAnimation(this, "pos"));
    this->setPos(scene()->width()/2 + this->boundingRect().width()/2,0);
    myState->assignProperty(this, "pos", QPointF(0,0));
    if(parentState)
        this->parentState->assignProperty(this, "pos", QPointF(scene()->width()/2 + this->boundingRect().width()/2,0));

    QKeyEventTransition *kdown = new QKeyEventTransition(win, QEvent::KeyPress, Qt::Key_Down);
    myState->addTransition(kdown);
    QKeyEventTransition *kup = new QKeyEventTransition(win, QEvent::KeyPress, Qt::Key_Up);
    myState->addTransition(kup);
    QKeyEventTransition *kleft = new QKeyEventTransition(win, QEvent::KeyPress, Qt::Key_Left);
    myState->addTransition(kleft);
    QKeyEventTransition *kright = new QKeyEventTransition(win, QEvent::KeyPress, Qt::Key_Right);
    myState->addTransition(kright);
    QKeyEventTransition *kenter = new QKeyEventTransition(win, QEvent::KeyPress, Qt::Key_Return);
    myState->addTransition(kenter);
    if(parentState){
        QKeyEventTransition *kesc = new QKeyEventTransition(win, QEvent::KeyPress, Qt::Key_Escape);
        kesc->setTargetState(parentState);
        myState->addTransition(kesc);
        connect(kesc, SIGNAL(triggered()), stepInto, SLOT(play()));
    }
    connect(kdown, SIGNAL(triggered()), this, SLOT(keyDown()));
    connect(kup, SIGNAL(triggered()), this, SLOT(keyUp()));
    connect(kleft, SIGNAL(triggered()), this, SLOT(keyLeft()));
    connect(kright, SIGNAL(triggered()), this, SLOT(keyRight()));
    connect(kenter, SIGNAL(triggered()), this, SLOT(keyEnter()));
}

void GraphicsMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    //Kistéglalap a kijelöléshez
    painter->setBrush(QColor(150,100,150,100));
    painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect().x(), selected*50-(sum*25), boundingRect().width(), 50);


    //Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    painter->drawText(QRectF(boundingRect().x(),-(sum*25 + 113), boundingRect().width(), 75).translated(4,4), title, QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(boundingRect().x(),-(sum*25 + 113), boundingRect().width(), 75), title, QTextOption(Qt::AlignCenter));

    //Elemek
    painter->setFont(itemFont);
    short i = 0;
    foreach (StatedItemObject m, menus) {
        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(boundingRect().x(), i*50-(sum*25), boundingRect().width(), 50).translated(4,4), m.title, QTextOption(Qt::AlignCenter));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(boundingRect().x(), i*50-(sum*25), boundingRect().width(), 50), m.title, QTextOption(Qt::AlignCenter));
        i++;
    }
    foreach (OptionItem o, options){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->drawText(QRectF(boundingRect().x()+2, i*50-(sum*25), boundingRect().width()-3, 50).translated(4,4), o.name(), QTextOption(Qt::AlignLeft));
        painter->drawText(QRectF(boundingRect().x()+2, i*50-(sum*25), boundingRect().width()-3, 50).translated(4,4), o.selected(), QTextOption(Qt::AlignRight));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(boundingRect().x()+2, i*50-(sum*25), boundingRect().width()-3, 50), o.name(), QTextOption(Qt::AlignLeft));
        painter->drawText(QRectF(boundingRect().x()+2, i*50-(sum*25), boundingRect().width()-3, 50), o.selected(), QTextOption(Qt::AlignRight));
        i++;
    }

    painter->restore();
}

QRectF GraphicsMenu::boundingRect() const
{
    return QRectF(-240,-(sum*25 + 113),480,117+sum*50);
}

GraphicsMenu* GraphicsMenu::addSubMenu(const QString &name)
{
    QState* child = new QState(myState->parentState());
    child->assignProperty(this, "pos", QPointF(-(scene()->width()/2 + this->boundingRect().width()/2),0));
    connect(child, SIGNAL(entered()), stepInto, SLOT(play()));
    GraphicsMenu* grMenu = new GraphicsMenu(name, myState, child, menuStep, stepInto, win);
    menus.append(*grMenu);
    sum++;

    switch(menus.size()){
    case 1:
        myState->addTransition(this, SIGNAL(menu1Selected()), child);
        break;
    case 2:
        myState->addTransition(this, SIGNAL(menu2Selected()), child);
        break;
    case 3:
        myState->addTransition(this, SIGNAL(menu3Selected()), child);
        break;
    case 4:
        myState->addTransition(this, SIGNAL(menu4Selected()), child);
        break;
    case 5:
        myState->addTransition(this, SIGNAL(menu5Selected()), child);
        break;
    case 6:
        myState->addTransition(this, SIGNAL(menu6Selected()), child);
        break;
    case 7:
        myState->addTransition(this, SIGNAL(menu7Selected()), child);
        break;
    }

    return grMenu;
}

void GraphicsMenu::addOptionItem(const QString &name, QVariant &variant, QVariantMap &vmap)
{
    options.push_back(OptionItem(name, variant, vmap));
    sum++;
}

void GraphicsMenu::addMenuItem(const QString &title, QState *targetState)
{
    targetState->assignProperty(this, "pos", QPointF(-(scene()->width()/2 + this->boundingRect().width()/2),0));
    menus.append(MenuItem(title, targetState));
    sum++;

    switch(menus.size()){
    case 1:
        myState->addTransition(this, SIGNAL(menu1Selected()), targetState);
        break;
    case 2:
        myState->addTransition(this, SIGNAL(menu2Selected()), targetState);
        break;
    case 3:
        myState->addTransition(this, SIGNAL(menu3Selected()), targetState);
        break;
    case 4:
        myState->addTransition(this, SIGNAL(menu4Selected()), targetState);
        break;
    case 5:
        myState->addTransition(this, SIGNAL(menu5Selected()), targetState);
        break;
    case 6:
        myState->addTransition(this, SIGNAL(menu6Selected()), targetState);
        break;
    case 7:
        myState->addTransition(this, SIGNAL(menu7Selected()), targetState);
        break;
    }
}

void GraphicsMenu::keyDown()
{
    if(selected >= sum-1) return;
    selected++;
    menuStep->play();
    update(boundingRect().x(), (selected-1)*50-(sum*25), boundingRect().width(), 100);
    return;
}

void GraphicsMenu::keyUp()
{
    if(selected == 0) return;
    selected--;
    menuStep->play();
    update(boundingRect().x(), selected*50-(sum*25), boundingRect().width(), 100);
    return;
}

void GraphicsMenu::keyLeft()
{
    if(selected < menus.size()) return;
    if(options[selected-menus.size()].prev())
        menuStep->play();
    update(boundingRect().x(), selected*50-(sum*25), boundingRect().width(), 50);
    return;
}

void GraphicsMenu::keyRight()
{
    if(selected < menus.size()) return;
    if(options[selected-menus.size()].next())
        menuStep->play();
    update(boundingRect().x(), selected*50-(sum*25), boundingRect().width(), 50);
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

void GraphicsMenu::setMenuStepSound(QSound *sound)
{
    menuStep = sound;
}

void GraphicsMenu::setIntoSound(QSound *sound)
{
    stepInto = sound;
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

















