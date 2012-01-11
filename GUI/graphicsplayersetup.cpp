#include "GUI/graphicsplayersetup.hpp"

GraphicsNPSetup::GraphicsNPSetup(QAbstractState *_backState, QState *_ownState)
{
    title = tr("Players setup");
    names[0] = tr("Local player");
    names[1] = tr("#1 Network player");
    names[2] = tr("#2 Network player");
    names[3] = tr("#3 Network player");
    selected = 1;
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(30);
    _ownState->machine()->addDefaultAnimation(new QPropertyAnimation(this, "pos"));
    _ownState->assignProperty(this, "pos", QPointF(0,0));
    connect(_ownState, SIGNAL(propertiesAssigned()), this, SLOT(setGrabKeyboard()));
    connect(this, SIGNAL(previousState()), this, SLOT(setUnGrabKeyboard()));
    _ownState->addTransition(this, SIGNAL(previousState()), _backState);
}

QRectF GraphicsNPSetup::boundingRect() const
{
    return QRectF(-366, -270, 650, 330);
}

void GraphicsNPSetup::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    // Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    painter->drawText(QRectF(-233,-266, 466, 66).translated(4,4), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-233,-266, 466, 66), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));

    //Kijelölés
    painter->setBrush(QColor(150,100,150,100));
    painter->setPen(Qt::NoPen);
    switch(selected){
    case 0:
        painter->drawRect(-366, -150, 300, 50);
        break;
    case 2:
        painter->drawRect(166, -150, 115, 50);
        break;
    case 10:
        painter->drawRect(-366, -100, 300, 50);
        break;
    case 20:
        painter->drawRect(-366, -50, 300, 50);
        break;
    case 30:
        painter->drawRect(-366, 0, 300, 50);
        break;
    }

    //Jelzők
    painter->setFont(itemFont);

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-360, -150, 300, 50).translated(2,3), names[0], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-360, -150, 300, 50), names[0], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-360, -100, 300, 50).translated(2,3), names[1], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-360, -100, 300, 50), names[1], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-360, -50, 300, 50).translated(2,3), names[2], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    if(ArawnSettings::instance()->noOfPlayers > 2)    painter->setPen(QColor(50, 150, 200));
    else                  painter->setPen(QColor(95, 95, 100));
    painter->drawText(QRectF(-360, -50, 300, 50), names[2], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-360, 0, 300, 50).translated(2,3), names[3], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    if(ArawnSettings::instance()->noOfPlayers > 3)    painter->setPen(QColor(50, 150, 200));
    else                  painter->setPen(QColor(95, 95, 100));
    painter->drawText(QRectF(-360, 0, 300, 50), names[3], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

    //Név
    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-33, -150, 166, 50).translated(2,3), (selected == 1 ? (ArawnSettings::instance()->defaultPlayer1Name).toString()+"_" : (ArawnSettings::instance()->defaultPlayer1Name).toString()), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    painter->drawLine(-31, -108, 133, -108);
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-33, -150, 166, 50), (selected == 1 ? (ArawnSettings::instance()->defaultPlayer1Name).toString()+"_" : (ArawnSettings::instance()->defaultPlayer1Name).toString()), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    painter->drawLine(-33, -110, 131, -110);

    // Szín
    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(166, -150, 110, 50).translated(2,3), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->defaultColor, "Blank"), QTextOption(Qt::AlignCenter));
    painter->setPen(QRgb(ArawnSettings::instance()->defaultColor.toInt()));
    painter->drawText(QRectF(166, -150, 110, 50), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->defaultColor, "Blank"), QTextOption(Qt::AlignCenter));


    painter->restore();
}

void GraphicsNPSetup::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) { emit previousState(); return; }

    switch(selected){
    case 0:
        if(event->key() == Qt::Key_Down) { selected = 10; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Right) { selected = 1; update(boundingRect()); return; }
        break;
    case 1:
        if(event->key() == Qt::Key_Left) { selected = 0; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Right) { selected = 2; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) { selected = 2; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Backspace) {
            if(ArawnSettings::instance()->defaultPlayer1Name.toString().length() == 0) return;
            ArawnSettings::instance()->defaultPlayer1Name =
                    ArawnSettings::instance()->defaultPlayer1Name.toString().section("", 0, ArawnSettings::instance()->defaultPlayer1Name.toString().length()-1);
            update(-360,-86, 362, 52);
            update(boundingRect()); return; }
        ArawnSettings::instance()->defaultPlayer1Name =
                ArawnSettings::instance()->defaultPlayer1Name.toString() + event->text();
        break;
    case 2:
        if(event->key() == Qt::Key_Left) { selected = 1; update(boundingRect()); return; }

        break;
    case 10:
        if(event->key() == Qt::Key_Up) { selected = 0; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Down) { selected = 20; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Right) { selected = 1; update(boundingRect()); return; }
        break;
    case 20:
        if(event->key() == Qt::Key_Up) { selected = 10; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Down) { selected = 30; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Right) { selected = 1; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space){
            ArawnSettings::instance()->noOfPlayers > 2 ? ArawnSettings::instance()->noOfPlayers = 2 : ArawnSettings::instance()->noOfPlayers = 3;
            update(boundingRect());
            return;
        }
        break;
    case 30:
        if(event->key() == Qt::Key_Up) { selected = 20; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Right) { selected = 1; update(boundingRect()); return; }
        if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space){
            ArawnSettings::instance()->noOfPlayers > 3 ? ArawnSettings::instance()->noOfPlayers = 3 : ArawnSettings::instance()->noOfPlayers = 4;
            update(boundingRect());
            return;
        }
        break;
    }
}

void GraphicsNPSetup::setGrabKeyboard()
{
    grabKeyboard();
}

void GraphicsNPSetup::setUnGrabKeyboard()
{
    ungrabKeyboard();
}






















