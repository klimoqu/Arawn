#include "arawnheader.h"
//#include <QtOpenGL/QtOpenGL>


void QArawnWindow::initWindow()
{

    QRect sr = QApplication::desktop()->screenGeometry();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::BlankCursor);
    setFrameStyle(QFrame::NoFrame);
//    if(ArawnSettings::instance()->openGlRendering.toBool()){
//        setViewport(new QGLWidget(QGLFormat(QGL::DoubleBuffer)));
//    }
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scale(((qreal)sr.width()) / (qreal)ArawnSettings::instance()->resolution.toPoint().x(),
          ((qreal)sr.height()) / (qreal)ArawnSettings::instance()->resolution.toPoint().y());


    scene = new QGraphicsScene(-(ArawnSettings::instance()->resolution.toPoint().x()/2),
                               -(ArawnSettings::instance()->resolution.toPoint().y()/2),
                               ArawnSettings::instance()->resolution.toPoint().x(),
                               ArawnSettings::instance()->resolution.toPoint().y(), this);
    scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    pixWelcomeItem = new PixmapObjectItem(QPixmap("res/KliMoQu.png"));
    pixWelcomeItem->setPos(-260, -190);
    scene->addItem(pixWelcomeItem);

    setBackgroundBrush(QBrush(Qt::black));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    setScene(scene);

    machine = new QStateMachine(this);
    stateLogo = new QState();
    connect(stateLogo, SIGNAL(entered()), this, SLOT(initializeOthers()));

    machine->addState(stateLogo);
    machine->setInitialState(stateLogo);
    machine->start();
}


void QArawnWindow::initializeOthers()
{
    QFontDatabase::addApplicationFont("res/screenge.ttf");
    QFontDatabase fdb;
    //font = fdb.font("Screengem", "Normal", 36);
    qApp->setFont(fdb.font("Screengem", "Normal", 36));

    sounds[0] = new QSound("res/0_tofrommenu.wav", this);
    sounds[1] = new QSound("res/1_changemenu.wav", this);
    sounds[2] = new QSound("res/2_step.vaw", this);
    sounds[3] = new QSound("res/3_putbomb.wav", this);
    sounds[4] = new QSound("res/4_explode.wav", this);
    sounds[5] = new QSound("res/5_getextra.wav", this);
    sounds[6] = new QSound("res/6_die.wav", this);
    sounds[7] = new QSound("res/7_splash1a.wav", this);
    sounds[8] = new QSound("res/8_splash2a.wav", this);
    sounds[9] = new QSound("res/9_corpse_explode.wav", this);
    sounds[10] = new QSound("res/10_deepfall.wav", this);
    sounds[11] = new QSound("res/11_hurry_up.wav", this);
    sounds[12] = new QSound("res/12_time_over.wav", this);
    sounds[13] = new QSound("res/13_klatsch.wav", this);
    sounds[14] = new QSound("res/arawn.wav", this);


//! [Arawnscreen részletei]

    pixFireItem = new PixmapObjectItem(QPixmap("res/fire.jpg")
        .scaled(scene->width(),scene->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    pixFireItem->setOpacity(0.0);
    pixArawnItem = new PixmapObjectItem(QPixmap("res/Arawn.png")
        .scaledToHeight(scene->height(), Qt::SmoothTransformation));
    pixArawnItem->setOpacity(0.0);
    pixHirItem = new PixmapObjectItem( QPixmap("res/hiryrvdydd.png")
        .scaledToWidth((3*scene->width())/4, Qt::SmoothTransformation));
    pixHirItem->setOpacity(0.0);

    pixArawnItem->setPos(scene->width()/2 - (pixArawnItem->boundingRect().width()) , -(pixArawnItem->boundingRect().height()/2));
    pixHirItem->setPos(- (pixHirItem->boundingRect().width()/2), - (pixHirItem->boundingRect().height()/2));
    //pixFireItem->setPos(-( pixFireItem->boundingRect()/2), 0);

    QPropertyAnimation *aanim = new QPropertyAnimation(pixArawnItem, "opacity", this);
        aanim->setStartValue(0.0);
        aanim->setEndValue(0.6);
        aanim->setDuration(1000);
    QPropertyAnimation *hanim = new QPropertyAnimation(pixHirItem, "opacity", this);
        hanim->setStartValue(0.0);
        hanim->setEndValue(0.9);
        hanim->setDuration(700);
    QPropertyAnimation *fanim = new QPropertyAnimation(pixFireItem, "opacity", this);
        fanim->setStartValue(0.0);
        fanim->setEndValue(0.5);
        fanim->setDuration(1000);

//!

//! [QStates]
    stateArawn = new QState();
        QTimer timerToStAr;
        timerToStAr.setSingleShot(true);
        QSignalTransition *trA = stateLogo->addTransition(&timerToStAr, SIGNAL(timeout()), stateArawn);
        trA->addAnimation(aanim);
        trA->addAnimation(hanim);
        trA->addAnimation(fanim);
        machine->addState(stateArawn);
        connect(stateArawn, SIGNAL(entered()), this, SLOT(showArawnScreen()));
        //
        //stateArawn->assignProperty(opEffectA, "opacity", 0.6);
        //stateArawn->assignProperty(opEffectH, "opacity", 0.9);
        //stateArawn->assignProperty(opEffectF, "opacity", 0.5);
        //

    stateMainMenu = new QState();



    //Végén
    timerToStAr.start(500);
}


void QArawnWindow::showArawnScreen()
{
    scene->removeItem(pixWelcomeItem);
    scene->addItem(pixArawnItem);
    scene->addItem(pixHirItem);
    scene->addItem(pixFireItem);
    playSound(14);

//    QGraphicsTextItem *t = new QGraphicsTextItem(0, scene);
//    t->setFont(qApp->font());
//    t->setPos(-100, 200);
//    t->setHtml("<font color='red'>Hello Arawn</font>");
//    scene->addItem(t);

}


void QArawnWindow::playSound(uchar n)
{
    sounds[n]->play();
}

void QArawnWindow::initializeMenus()
{
    menuMain = new GraphicsMenu(tr("Main Menu"));
    menuMain->addMenuItem(tr("Local Game"));
    menuMain->addMenuItem(tr("Network Game"));
    menuMain->addMenuItem(tr("Options"));
    menuMain->addMenuItem(tr("Map editor"));
    menuMain->addMenuItem(tr("About"));
    menuMain->addMenuItem(tr("Quit"));


    menuLocalGame = new GraphicsMenu(tr("Local Game"));
    menuLocalGame->addMenuItem(tr("Player setup"));
    menuLocalGame->addMenuItem(tr("Map selection"));
    menuLocalGame->addMenuItem(tr("Game settings"));
    menuLocalGame->addMenuItem(tr("Start survival cup"));
    menuLocalGame->addMenuItem(tr("Start murder cup"));
    menuLocalGame->addMenuItem(tr("Load saved cup"));


    menuGameSettings = new GraphicsMenu(tr("Game Settings"));
    menuGameSettings->addMenuItem(tr("Start/max extras"));
    menuGameSettings->addMenuItem(tr("Enable/disable extras"));
    menuGameSettings->addOptionItem(tr("Round time"), ArawnSettings::instance()->roundTimeDefault, ArawnSettings::instance()->roundTimeDefaultValues);
    menuGameSettings->addOptionItem(tr("Points to win"), ArawnSettings::instance()->pointsToWin, ArawnSettings::instance()->pointsToWinValues);
    menuGameSettings->addOptionItem(tr("Bomb timer n/10s"), ArawnSettings::instance()->bombTimer, ArawnSettings::instance()->bombTimerValues);
    menuGameSettings->addOptionItem(tr("Bomb speed 1/10s"), ArawnSettings::instance()->bombSpeed, ArawnSettings::instance()->bombSpeedValues);


    menuSMExtras = new GraphicsMenu(tr("Start/max extras"));
    menuSMExtras->addOptionItem(tr("Start bombs"), ArawnSettings::instance()->startBombs, ArawnSettings::instance()->startBombsValues);
    menuSMExtras->addOptionItem(tr("Max bombs"), ArawnSettings::instance()->maxBombs, ArawnSettings::instance()->maxBombsValues);
    menuSMExtras->addOptionItem(tr("Start power"), ArawnSettings::instance()->startFire, ArawnSettings::instance()->startFireValues);
    menuSMExtras->addOptionItem(tr("Max power"), ArawnSettings::instance()->maxFire, ArawnSettings::instance()->maxFireValues);
    menuSMExtras->addOptionItem(tr("Start speed"), ArawnSettings::instance()->startSpeed, ArawnSettings::instance()->startSpeedValues);
    menuSMExtras->addOptionItem(tr("Max speed"), ArawnSettings::instance()->maxSpeed, ArawnSettings::instance()->maxSpeedValues);
/*...*/

    menuNetworkGame = new GraphicsMenu(tr("Network Game"));
    menuNetworkGame->addMenuItem(tr("Create"));
    menuNetworkGame->addMenuItem(tr("Connect"));
    /*...*/

    menuOptions = new GraphicsMenu(tr("Options"));
}

void QArawnWindow::showMainMenu()
{

}










