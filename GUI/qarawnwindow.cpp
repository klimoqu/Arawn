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
    //setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setRenderHint(QPainter::SmoothPixmapTransform);
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
    sounds[2] = new QSound("res/2_step.wav", this);
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
    pixFireItem->setPos(-(scene->width()/2), -((pixFireItem->boundingRect().height())-(scene->height()/2)) );

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
        fanim->setDuration(1200);

//!

//! [QStates]
    stateArawn = new QState;
    machine->addState(stateArawn);
    stateMainMenu = new QState;
    machine->addState(stateMainMenu);
    stateLocalGameMenu = new QState;
    machine->addState(stateLocalGameMenu);
    statePlayerSetup = new QState;
    machine->addState(statePlayerSetup);
    stateMapSelection = new QState;
    machine->addState(stateMapSelection);
    stateGameSettings = new QState;
    machine->addState(stateGameSettings);
    stateSMExtras = new QState;
    machine->addState(stateSMExtras);
    stateEDDiseases = new QState;
    machine->addState(stateEDDiseases);
    stateLoad = new QState;
    machine->addState(stateLoad);
    stateNetworkGameMenu = new QState;
    machine->addState(stateNetworkGameMenu);
    stateOptionsMenu = new QState;
    machine->addState(stateOptionsMenu);
    stateMapEditor = new QState;
    machine->addState(stateMapEditor);
    stateAbout = new QState;
    machine->addState(stateAbout);
    finalState = new QFinalState;
    machine->addState(finalState);
    initializeMenus();

    QTimer *timerStLogoToStArawn = new QTimer(this);
    timerStLogoToStArawn->setSingleShot(true);
    QTimer *timerStArawnToStMM = new QTimer(this);
    timerStArawnToStMM->setSingleShot(true);
    timerStArawnToStMM->setInterval(3500);

    QSignalTransition *trA = stateLogo->addTransition(timerStLogoToStArawn, SIGNAL(timeout()), stateArawn);
    trA->addAnimation(aanim);
    trA->addAnimation(hanim);
    trA->addAnimation(fanim);
    connect(stateArawn, SIGNAL(entered()), this, SLOT(showArawnScreen()));
    connect(stateArawn, SIGNAL(entered()), timerStArawnToStMM, SLOT(start()));
    connect(stateArawn, SIGNAL(exited()), this, SLOT(enterMenus()));
    connect(stateArawn, SIGNAL(exited()), sounds[0], SLOT(play()));

    stateArawn->addTransition(timerStArawnToStMM, SIGNAL(timeout()), stateMainMenu);

    //Végén
    timerStLogoToStArawn->start(100);
    connect(machine, SIGNAL(finished()), this, SLOT(close()));
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
     scene->addItem(menuMain);
     menuMain->setPos(scene->width()/2 + menuMain->boundingRect().width()/2,0);
     stateMainMenu->assignProperty(menuMain, "pos", QPointF(0,0));
     machine->addDefaultAnimation(new QPropertyAnimation(menuMain, "pos"));
     QKeyEventTransition *k0 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Down);
     stateMainMenu->addTransition(k0);
     connect(k0, SIGNAL(triggered()), menuMain, SLOT(keyDown()));
     connect(k0, SIGNAL(triggered()), sounds[2], SLOT(play()));
     QKeyEventTransition *k1 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Up);
     stateMainMenu->addTransition(k1);
     connect(k1, SIGNAL(triggered()), menuMain, SLOT(keyUp()));
     connect(k1, SIGNAL(triggered()), sounds[2], SLOT(play()));
     QKeyEventTransition *k2 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Escape);
     k2->setTargetState(finalState);
     stateMainMenu->addTransition(k2);
     connect(k2, SIGNAL(triggered()), sounds[0], SLOT(play()));




     menuLocalGame = new GraphicsMenu(tr("Local Game"));
     menuLocalGame->addMenuItem(tr("Player setup"));
     menuLocalGame->addMenuItem(tr("Map selection"));
     menuLocalGame->addMenuItem(tr("Game settings"));
     menuLocalGame->addMenuItem(tr("Start survival cup"));
     menuLocalGame->addMenuItem(tr("Start murder cup"));
     menuLocalGame->addMenuItem(tr("Load saved cup"));
     scene->addItem(menuLocalGame);
     menuLocalGame->setPos(scene->width()/2 + menuLocalGame->boundingRect().width()/2,0);
     stateLocalGameMenu->assignProperty(menuLocalGame, "pos", QPointF(0,0));
     machine->addDefaultAnimation(new QPropertyAnimation(menuLocalGame, "pos"));


     menuGameSettings = new GraphicsMenu(tr("Game Settings"));
     menuGameSettings->addMenuItem(tr("Start/max extras"));
     menuGameSettings->addMenuItem(tr("Enable/disable diseases"));
     menuGameSettings->addOptionItem(tr("Round time"), ArawnSettings::instance()->roundTimeDefault, ArawnSettings::instance()->roundTimeDefaultValues);
     menuGameSettings->addOptionItem(tr("Points to win"), ArawnSettings::instance()->pointsToWin, ArawnSettings::instance()->pointsToWinValues);
     menuGameSettings->addOptionItem(tr("Bomb timer n/10s"), ArawnSettings::instance()->bombTimer, ArawnSettings::instance()->bombTimerValues);
     menuGameSettings->addOptionItem(tr("Bomb speed n*field/10s"), ArawnSettings::instance()->bombSpeed, ArawnSettings::instance()->bombSpeedValues);
     scene->addItem(menuGameSettings);
     menuGameSettings->setPos(scene->width()/2 + menuGameSettings->boundingRect().width()/2,0);
     stateGameSettings->assignProperty(menuGameSettings, "pos", QPointF(0,0));
     machine->addDefaultAnimation(new QPropertyAnimation(menuGameSettings, "pos"));


     menuSMExtras = new GraphicsMenu(tr("Start/max extras"));
     menuSMExtras->addOptionItem(tr("Start bombs"), ArawnSettings::instance()->startBombs, ArawnSettings::instance()->startBombsValues);
     menuSMExtras->addOptionItem(tr("Max bombs"), ArawnSettings::instance()->maxBombs, ArawnSettings::instance()->maxBombsValues);
     menuSMExtras->addOptionItem(tr("Start power"), ArawnSettings::instance()->startFire, ArawnSettings::instance()->startFireValues);
     menuSMExtras->addOptionItem(tr("Max power"), ArawnSettings::instance()->maxFire, ArawnSettings::instance()->maxFireValues);
     menuSMExtras->addOptionItem(tr("Start speed"), ArawnSettings::instance()->startSpeed, ArawnSettings::instance()->startSpeedValues);
     menuSMExtras->addOptionItem(tr("Max speed"), ArawnSettings::instance()->maxSpeed, ArawnSettings::instance()->maxSpeedValues);
     menuSMExtras->addOptionItem(tr("Start gloves"), ArawnSettings::instance()->startDropBombs, ArawnSettings::instance()->startDropBombsValues);
     menuSMExtras->addOptionItem(tr("Start boot"), ArawnSettings::instance()->startPushBombs, ArawnSettings::instance()->startPushBombsValues);
     scene->addItem(menuSMExtras);
     menuSMExtras->setPos(scene->width()/2 + menuSMExtras->boundingRect().width()/2,0);
     stateSMExtras->assignProperty(menuSMExtras, "pos", QPointF(0,0));
     machine->addDefaultAnimation(new QPropertyAnimation(menuSMExtras, "pos"));


     menuEDDiseases = new GraphicsMenu(tr("Enable/disable diseases"));
     menuEDDiseases->addOptionItem(tr("Failing bombs"), ArawnSettings::instance()->enableFailingBombs, ArawnSettings::instance()->enableFailingBombsValues);
     menuEDDiseases->addOptionItem(tr("Opposite controls"), ArawnSettings::instance()->enableOppositeControls, ArawnSettings::instance()->enableOppositeControlsValues);
     menuEDDiseases->addOptionItem(tr("Invisibility"), ArawnSettings::instance()->enableInvisibility, ArawnSettings::instance()->enableInvisibilityValues);
     scene->addItem(menuEDDiseases);
     menuEDDiseases->setPos(scene->width()/2 + menuEDDiseases->boundingRect().width()/2,0);
     stateEDDiseases->assignProperty(menuEDDiseases, "pos", QPointF(0,0));
     machine->addDefaultAnimation(new QPropertyAnimation(menuEDDiseases, "pos"));


     menuNetworkGame = new GraphicsMenu(tr("Network Game"));
     menuNetworkGame->addMenuItem(tr("Create"));
     menuNetworkGame->addMenuItem(tr("Connect"));
     scene->addItem(menuNetworkGame);
     /** TODO Itt még át kell gondolni */
     menuNetworkGame->setPos(scene->width()/2 + menuNetworkGame->boundingRect().width()/2,0);
     stateNetworkGameMenu->assignProperty(menuNetworkGame, "pos", QPointF(0,0));
     machine->addDefaultAnimation(new QPropertyAnimation(menuNetworkGame, "pos"));


     menuOptions = new GraphicsMenu(tr("Options"));
     menuOptions->addOptionItem(tr("Show corpse parts"), ArawnSettings::instance()->showCorpseParts, ArawnSettings::instance()->showCorpsePartsValues);
     menuOptions->addOptionItem(tr("Shaky explosion"), ArawnSettings::instance()->shakyExplosion, ArawnSettings::instance()->shakyExplosionValues);
     menuOptions->addOptionItem(tr("OpenGL"), ArawnSettings::instance()->openGlRendering, ArawnSettings::instance()->openGlRenderingValues);
     menuOptions->addOptionItem(tr("Resolution"), ArawnSettings::instance()->resolution, ArawnSettings::instance()->resolutionValues);
     menuOptions->addOptionItem(tr("Language"), ArawnSettings::instance()->language, ArawnSettings::instance()->languageValues);
     scene->addItem(menuOptions);
     menuOptions->setPos(scene->width()/2 + menuOptions->boundingRect().width()/2,0);
     stateOptionsMenu->assignProperty(menuOptions, "pos", QPointF(0,0));
     machine->addDefaultAnimation(new QPropertyAnimation(menuOptions, "pos"));

}


void QArawnWindow::showArawnScreen()
{
    scene->removeItem(pixWelcomeItem);
    scene->addItem(pixFireItem);
    scene->addItem(pixArawnItem);
    scene->addItem(pixHirItem);
    playSound(14);

}

void QArawnWindow::playSound(uchar n)
{
    sounds[n]->play();
}

void QArawnWindow::close()
{
    //! TODO mentés
    //ArawnSettings::instance()->save();
    QGraphicsView::close();
}

void QArawnWindow::enterMenus()
{
    scene->removeItem(pixArawnItem);
    scene->removeItem(pixHirItem);
    pixFireItem->setZValue(-2);

    copyright = new QGraphicsTextItem("Arawn 0.9b Copyright KliMoQu @ PPKE ITK");
    QFont fnt = qApp->font();
    fnt.setPixelSize(20);
    copyright->setFont(fnt);
    copyright->setOpacity(0.7);
    copyright->setPos(-(scene->width()/2)+5,(scene->height()/2)-30);
    QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect(copyright);
    dse->setColor(Qt::red);
    dse->setOffset(1.5);
    copyright->setGraphicsEffect(dse);
    scene->addItem(copyright);
}




