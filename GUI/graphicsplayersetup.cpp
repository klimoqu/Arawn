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
    _ownState->machine()->addDefaultAnimation(new QPropertyAnimation(this, "pos")); /// Alapértelmezett animáció
    _ownState->assignProperty(this, "pos", QPointF(0,0)); /// Saját állapotra kényszerített hely
    connect(_ownState, SIGNAL(propertiesAssigned()), this, SLOT(setGrabKeyboard())); /// Ha elérte a helyét, legyen billentyűzet
    connect(this, SIGNAL(previousState()), this, SLOT(setUnGrabKeyboard())); /// Visszalépéskor engedje el
    _ownState->addTransition(this, SIGNAL(previousState()), _backState); /// SignalTransition a visszalépéshez
}

QRectF GraphicsNPSetup::boundingRect() const
{
    return QRectF(-366, -270, 650, 330); /// Hard coded kiterjedés, 0,0 középponthoz képest
}

void GraphicsNPSetup::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save(); /// save->restore a gyorsabb rajzolásért

    // Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    /// Először mindig az árnyékot rajzoljuk, 4,4-es eltolással
    painter->drawText(QRectF(-233,-266, 466, 66).translated(4,4), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-233,-266, 466, 66), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));

    //Kijelölés
    painter->setBrush(QColor(150,100,150,100));
    painter->setPen(Qt::NoPen);
    /// Itt lesz majd egy kicsit komplexebb feladat. A szövegmezőre nem rajzolunk téglalapot kijelöléskor, de a színmezőre igen.
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

    //Jelzők(names[x])
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
    /// A játékosszám függvényében szürke/szines
    if(ArawnSettings::instance()->noOfPlayers > 2) painter->setPen(QColor(50, 150, 200));
    else painter->setPen(QColor(95, 95, 100));
    painter->drawText(QRectF(-360, -50, 300, 50), names[2], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-360, 0, 300, 50).translated(2,3), names[3], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    if(ArawnSettings::instance()->noOfPlayers > 3) painter->setPen(QColor(50, 150, 200));
    else painter->setPen(QColor(95, 95, 100));
    painter->drawText(QRectF(-360, 0, 300, 50), names[3], QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

    //Név
    /// Itt is több kell majd, hiszen mindenkinek van neve (ArawnSettings), és mindegyik szerkeszthető is
    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(-33, -150, 166, 50).translated(2,3), (selected == 1 ? (ArawnSettings::instance()->defaultPlayer1Name).toString()+"_" : (ArawnSettings::instance()->defaultPlayer1Name).toString()), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    painter->drawLine(-31, -108, 133, -108);
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-33, -150, 166, 50), (selected == 1 ? (ArawnSettings::instance()->defaultPlayer1Name).toString()+"_" : (ArawnSettings::instance()->defaultPlayer1Name).toString()), QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    painter->drawLine(-33, -110, 131, -110);

    // Szín
    /// Fentihez hasonlóan
    painter->setPen(QColor(100, 10, 10, 200));
    painter->drawText(QRectF(166, -150, 110, 50).translated(2,3), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default1Color, "Blank"), QTextOption(Qt::AlignCenter));
    painter->setPen(QRgb(ArawnSettings::instance()->default1Color.toInt()));
    painter->drawText(QRectF(166, -150, 110, 50), (ArawnSettings::instance()->colorValues).key(ArawnSettings::instance()->default1Color, "Blank"), QTextOption(Qt::AlignCenter));


    painter->restore();
}

// Ugyan így, csak több case-ág van.
void GraphicsNPSetup::keyPressEvent(QKeyEvent *event)
{
    // Az esc minden kijelölésre ugyan azt csinálja
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
        update(boundingRect());
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





















