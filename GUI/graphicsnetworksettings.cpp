#include "GUI/graphicsnetworksettings.hpp"
#include "arawnsettings.hpp"

GraphicsNetworkSettings::GraphicsNetworkSettings(QAbstractState *_backState, QState *_ownState, QState *_nextState, QArawnWindow *window)
{
    win = window;
    ownState = _ownState;
    backState = _backState;
    nextState = _nextState;
    lineEdit = ArawnSettings::instance()->defaultIPAddress;
    title = tr("Connect to network");
    text = tr("Enter the IP address or hostname:");
    connectText = tr("Connect");
    connecting = tr("Connecting...");
    titFont = qApp->font();
    titFont.setPixelSize(50);
    itemFont = qApp->font();
    itemFont.setPixelSize(40);
    lineFont = qApp->font();
    lineFont.setPixelSize(30);
    selected = 1;
    ownState->machine()->addDefaultAnimation(new QPropertyAnimation(this, "pos"));
    ownState->assignProperty(this, "pos", QPointF(0,0));
    connect(ownState, SIGNAL(propertiesAssigned()), this, SLOT(setGrabKeyboard()));
    connect(this, SIGNAL(previousState()), this, SLOT(setUnGrabKeyboard()));
    ownState->addTransition(this, SIGNAL(previousState()), backState);
}

QRectF GraphicsNetworkSettings::boundingRect() const
{
    return QRectF(-366, -270, 640, 430);
}

void GraphicsNetworkSettings::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    // Cím
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(titFont);
    painter->drawText(QRectF(-266,-266, 533, 66).translated(4,4), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-266,-266, 533, 66), title, QTextOption(Qt::AlignCenter | Qt::AlignTop));

    // Szöveg
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(lineFont);
    painter->drawText(QRectF(-360,-150, 630, 50).translated(2,3), text, QTextOption(Qt::AlignLeading));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-360,-150, 630, 50), text, QTextOption(Qt::AlignLeading));

    // Sor +kijelölve?
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(lineFont);
    painter->drawText(QRectF(-360,-86, 360, 50).translated(2,3), (selected == 0 ? lineEdit.toString()+"_" : lineEdit.toString()), QTextOption(Qt::AlignLeading));
    painter->drawLine(-358, -46, 2, -46);
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-360,-86, 360, 50), (selected == 0 ? lineEdit.toString()+"_" : lineEdit.toString()), QTextOption(Qt::AlignLeading));
    painter->drawLine(-360, -48, 0, -48);

    // Gomb /kijelölve?
    if(selected == 1){
        painter->setBrush(QColor(150,100,150,100));
        painter->setPen(Qt::NoPen);
        painter->drawRect(-150,0,300,55);
    }
    painter->setPen(QColor(100, 10, 10, 200));
    painter->setFont(itemFont);
    painter->drawText(QRectF(-150,0,300,55).translated(3,3), connectText, QTextOption(Qt::AlignCenter));
    painter->setPen(QColor(50, 150, 200));
    painter->drawText(QRectF(-150,0,300,55), connectText, QTextOption(Qt::AlignCenter));

    // Connecting
    if(selected == 2){
        painter->setPen(QColor(100, 10, 10, 200));
        painter->setFont(lineFont);
        painter->drawText(QRectF(-360, 100, 360, 50).translated(2,3), connecting, QTextOption(Qt::AlignLeading));
        painter->setPen(QColor(50, 150, 200));
        painter->drawText(QRectF(-360, 100, 360, 50), connecting, QTextOption(Qt::AlignLeading));
    }

    painter->restore();
}

void GraphicsNetworkSettings::keyPressEvent(QKeyEvent *event)
{
    if(selected == 0){
        switch(event->key()){
        case Qt::Key_Down:
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Tab:
            selected = 1;
            update(-360,-86, 362, 52);
            update(-150,0,300,55);
            return;
        case Qt::Key_Backspace:
        case Qt::Key_Left:
            if(lineEdit.toString().length() == 0) return;
            lineEdit = lineEdit.toString().section("", 0, lineEdit.toString().length()-1);
            update(-360,-86, 362, 52);
            return;
        case Qt::Key_Escape:
            emit previousState();
            return;
        default:
            lineEdit = lineEdit.toString() + event->text();
            update(-360,-86, 362, 52);
            return;
        }
    }
    if(selected == 1){
        switch(event->key()){
        case Qt::Key_Up:
        case Qt::Key_Tab:
            selected = 0;
            update(-360,-86, 362, 52);
            update(-150,0,300,55);
            return;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            connecting = tr("Connecting...");
            emit startConnecting();
            selected = 2;
            update(-150,0,300,55);
            update(-360, 100, 362, 52);
            return;
        case Qt::Key_Escape:
            emit previousState();
            return;
        }
    }
    if(selected == 2 && event->key() == Qt::Key_Escape){
        selected = 0;
        update(-360,-86, 362, 52);
        update(-360, 100, 362, 52);
        return;
    }
}

void GraphicsNetworkSettings::setGrabKeyboard()
{
    grabKeyboard();
}

void GraphicsNetworkSettings::setUnGrabKeyboard()
{
    ungrabKeyboard();
}

void GraphicsNetworkSettings::connectionFail()
{
    connecting = tr("Fail!");
    update(-360, 100, 362, 52);
}














