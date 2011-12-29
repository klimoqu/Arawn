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
     connect(menuMain, SIGNAL(menuChanged()), sounds[2], SLOT(play()), Qt::DirectConnection);
     scene->addItem(menuMain);
     menuMain->setPos(scene->width()/2 + menuMain->boundingRect().width()/2,0);
     machine->addDefaultAnimation(new QPropertyAnimation(menuMain, "pos"));



     menuLocalGame = new GraphicsMenu(tr("Local Game"));
     menuLocalGame->addMenuItem(tr("Player setup"));
     menuLocalGame->addMenuItem(tr("Map selection"));
     menuLocalGame->addMenuItem(tr("Game settings"));
     menuLocalGame->addMenuItem(tr("Start survival cup"));
     menuLocalGame->addMenuItem(tr("Start murder cup"));
     menuLocalGame->addMenuItem(tr("Load saved cup"));
     connect(menuLocalGame, SIGNAL(menuChanged()), sounds[2], SLOT(play()), Qt::DirectConnection);
     scene->addItem(menuLocalGame);
     menuLocalGame->setPos(scene->width()/2 + menuLocalGame->boundingRect().width()/2,0);
     machine->addDefaultAnimation(new QPropertyAnimation(menuLocalGame, "pos"));


     menuGameSettings = new GraphicsMenu(tr("Game Settings"));
     menuGameSettings->addMenuItem(tr("Start/max extras"));
     menuGameSettings->addMenuItem(tr("Enable/disable diseases"));
     menuGameSettings->addOptionItem(tr("Round time"), ArawnSettings::instance()->roundTimeDefault, ArawnSettings::instance()->roundTimeDefaultValues);
     menuGameSettings->addOptionItem(tr("Points to win"), ArawnSettings::instance()->pointsToWin, ArawnSettings::instance()->pointsToWinValues);
     menuGameSettings->addOptionItem(tr("Bomb timer n/10s"), ArawnSettings::instance()->bombTimer, ArawnSettings::instance()->bombTimerValues);
     menuGameSettings->addOptionItem(tr("Bomb speed n*field/10s"), ArawnSettings::instance()->bombSpeed, ArawnSettings::instance()->bombSpeedValues);
     connect(menuGameSettings, SIGNAL(menuChanged()), sounds[2], SLOT(play()), Qt::DirectConnection);
     scene->addItem(menuGameSettings);
     menuGameSettings->setPos(scene->width()/2 + menuGameSettings->boundingRect().width()/2,0);
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
     connect(menuSMExtras, SIGNAL(menuChanged()), sounds[2], SLOT(play()), Qt::DirectConnection);
     scene->addItem(menuSMExtras);
     menuSMExtras->setPos(scene->width()/2 + menuSMExtras->boundingRect().width()/2,0);
     machine->addDefaultAnimation(new QPropertyAnimation(menuSMExtras, "pos"));


     menuEDDiseases = new GraphicsMenu(tr("Enable/disable diseases"));
     menuEDDiseases->addOptionItem(tr("Failing bombs"), ArawnSettings::instance()->enableFailingBombs, ArawnSettings::instance()->enableFailingBombsValues);
     menuEDDiseases->addOptionItem(tr("Opposite controls"), ArawnSettings::instance()->enableOppositeControls, ArawnSettings::instance()->enableOppositeControlsValues);
     menuEDDiseases->addOptionItem(tr("Invisibility"), ArawnSettings::instance()->enableInvisibility, ArawnSettings::instance()->enableInvisibilityValues);
     connect(menuEDDiseases, SIGNAL(menuChanged()), sounds[2], SLOT(play()), Qt::DirectConnection);
     scene->addItem(menuEDDiseases);
     menuEDDiseases->setPos(scene->width()/2 + menuEDDiseases->boundingRect().width()/2,0);
     machine->addDefaultAnimation(new QPropertyAnimation(menuEDDiseases, "pos"));


     menuNetworkGame = new GraphicsMenu(tr("Network Game"));
     menuNetworkGame->addMenuItem(tr("Create"));
     menuNetworkGame->addMenuItem(tr("Connect"));
     connect(menuNetworkGame, SIGNAL(menuChanged()), sounds[2], SLOT(play()), Qt::DirectConnection);
     scene->addItem(menuNetworkGame);
     /** TODO Itt még át kell gondolni */
     menuNetworkGame->setPos(scene->width()/2 + menuNetworkGame->boundingRect().width()/2,0);
     machine->addDefaultAnimation(new QPropertyAnimation(menuNetworkGame, "pos"));


     menuOptions = new GraphicsMenu(tr("Options"));
     menuOptions->addOptionItem(tr("Show corpse parts"), ArawnSettings::instance()->showCorpseParts, ArawnSettings::instance()->showCorpsePartsValues);
     menuOptions->addOptionItem(tr("Shaky explosion"), ArawnSettings::instance()->shakyExplosion, ArawnSettings::instance()->shakyExplosionValues);
     menuOptions->addOptionItem(tr("OpenGL"), ArawnSettings::instance()->openGlRendering, ArawnSettings::instance()->openGlRenderingValues);
     menuOptions->addOptionItem(tr("Resolution"), ArawnSettings::instance()->resolution, ArawnSettings::instance()->resolutionValues);
     menuOptions->addOptionItem(tr("Language"), ArawnSettings::instance()->language, ArawnSettings::instance()->languageValues);
     connect(menuOptions, SIGNAL(menuChanged()), sounds[2], SLOT(play()), Qt::DirectConnection);
     scene->addItem(menuOptions);
     menuOptions->setPos(scene->width()/2 + menuOptions->boundingRect().width()/2,0);
     machine->addDefaultAnimation(new QPropertyAnimation(menuOptions, "pos"));

//////////////////

     stateMainMenu->assignProperty(menuMain, "pos", QPointF(0,0));
     stateMainMenu->assignProperty(menuLocalGame, "pos", QPointF(scene->width()/2 + menuLocalGame->boundingRect().width()/2,0));
     stateMainMenu->assignProperty(menuNetworkGame, "pos", QPointF(scene->width()/2 + menuNetworkGame->boundingRect().width()/2,0));
     stateMainMenu->assignProperty(menuOptions, "pos", QPointF(scene->width()/2 + menuOptions->boundingRect().width()/2,0));
     stateMainMenu->addTransition(menuMain, SIGNAL(menu1Selected()), stateLocalGameMenu);
     stateMainMenu->addTransition(menuMain, SIGNAL(menu2Selected()), stateNetworkGameMenu);
     stateMainMenu->addTransition(menuMain, SIGNAL(menu3Selected()), stateOptionsMenu);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu4Selected()), stateMapEditor);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu5Selected()), stateAbout);
     stateMainMenu->addTransition(menuMain, SIGNAL(menu6Selected()), finalState);
     QKeyEventTransition *k0 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Down);
     stateMainMenu->addTransition(k0);
     connect(k0, SIGNAL(triggered()), menuMain, SLOT(keyDown()));
     QKeyEventTransition *k1 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Up);
     stateMainMenu->addTransition(k1);
     connect(k1, SIGNAL(triggered()), menuMain, SLOT(keyUp()));
     QKeyEventTransition *k3 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Return);
     stateMainMenu->addTransition(k3);
     connect(k3, SIGNAL(triggered()), menuMain, SLOT(keyEnter()));


     stateLocalGameMenu->assignProperty(menuMain, "pos", QPointF(-(scene->width()/2 + menuMain->boundingRect().width()/2),0));
     stateLocalGameMenu->assignProperty(menuLocalGame, "pos", QPointF(0,0));
     stateLocalGameMenu->assignProperty(menuGameSettings, "pos", QPointF(scene->width()/2 + menuGameSettings->boundingRect().width()/2,0));
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu1Selected()), stateLocalGameMenu);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu2Selected()), stateNetworkGameMenu);
     stateLocalGameMenu->addTransition(menuLocalGame, SIGNAL(menu3Selected()), stateGameSettings);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu4Selected()), stateMapEditor);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu5Selected()), stateAbout);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu6Selected()), finalState);
     QKeyEventTransition *k4 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Down);
     stateLocalGameMenu->addTransition(k4);
     connect(k4, SIGNAL(triggered()), menuLocalGame, SLOT(keyDown()));
     QKeyEventTransition *k5 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Up);
     stateLocalGameMenu->addTransition(k5);
     connect(k5, SIGNAL(triggered()), menuLocalGame, SLOT(keyUp()));
     QKeyEventTransition *k6 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Escape);
     k6->setTargetState(stateMainMenu);
     stateLocalGameMenu->addTransition(k6);
     QKeyEventTransition *k7 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Return);
     stateLocalGameMenu->addTransition(k7);
     connect(k7, SIGNAL(triggered()), menuLocalGame, SLOT(keyEnter()));


     stateGameSettings->assignProperty(menuLocalGame, "pos", QPointF(-(scene->width()/2 + menuLocalGame->boundingRect().width()/2),0));
     stateGameSettings->assignProperty(menuGameSettings, "pos", QPointF(0,0));
     stateGameSettings->assignProperty(menuSMExtras, "pos", QPointF(scene->width()/2 + menuSMExtras->boundingRect().width()/2,0));
     stateGameSettings->assignProperty(menuEDDiseases, "pos", QPointF(scene->width()/2 + menuEDDiseases->boundingRect().width()/2,0));
     stateGameSettings->addTransition(menuGameSettings, SIGNAL(menu1Selected()), stateSMExtras);
     stateGameSettings->addTransition(menuGameSettings, SIGNAL(menu2Selected()), stateEDDiseases);
     QKeyEventTransition *k8 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Down);
     stateGameSettings->addTransition(k8);
     connect(k8, SIGNAL(triggered()), menuGameSettings, SLOT(keyDown()));
     QKeyEventTransition *k9 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Up);
     stateGameSettings->addTransition(k9);
     connect(k9, SIGNAL(triggered()), menuGameSettings, SLOT(keyUp()));
     QKeyEventTransition *k10 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Left);
     stateGameSettings->addTransition(k10);
     connect(k10, SIGNAL(triggered()), menuGameSettings, SLOT(keyLeft()));
     QKeyEventTransition *k11 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Right);
     stateGameSettings->addTransition(k11);
     connect(k11, SIGNAL(triggered()), menuGameSettings, SLOT(keyRight()));
     QKeyEventTransition *k12 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Escape);
     k12->setTargetState(stateLocalGameMenu);
     stateGameSettings->addTransition(k12);
     QKeyEventTransition *k13 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Return);
     stateGameSettings->addTransition(k13);
     connect(k13, SIGNAL(triggered()), menuGameSettings, SLOT(keyEnter()));


     stateSMExtras->assignProperty(menuGameSettings, "pos", QPointF(-(scene->width()/2 + menuGameSettings->boundingRect().width()/2),0));
     stateSMExtras->assignProperty(menuSMExtras, "pos", QPointF(0,0));
     QKeyEventTransition *k14 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Down);
     stateSMExtras->addTransition(k14);
     connect(k14, SIGNAL(triggered()), menuSMExtras, SLOT(keyDown()));
     QKeyEventTransition *k15 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Up);
     stateSMExtras->addTransition(k15);
     connect(k15, SIGNAL(triggered()), menuSMExtras, SLOT(keyUp()));
     QKeyEventTransition *k16 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Left);
     stateSMExtras->addTransition(k16);
     connect(k16, SIGNAL(triggered()), menuSMExtras, SLOT(keyLeft()));
     QKeyEventTransition *k17 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Right);
     stateSMExtras->addTransition(k17);
     connect(k17, SIGNAL(triggered()), menuSMExtras, SLOT(keyRight()));
     QKeyEventTransition *k18 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Escape);
     k18->setTargetState(stateGameSettings);
     stateSMExtras->addTransition(k18);


     stateEDDiseases->assignProperty(menuGameSettings, "pos", QPointF(-(scene->width()/2 + menuGameSettings->boundingRect().width()/2),0));
     stateEDDiseases->assignProperty(menuEDDiseases, "pos", QPointF(0,0));
     QKeyEventTransition *k19 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Down);
     stateEDDiseases->addTransition(k19);
     connect(k19, SIGNAL(triggered()), menuEDDiseases, SLOT(keyDown()));
     QKeyEventTransition *k20 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Up);
     stateEDDiseases->addTransition(k20);
     connect(k20, SIGNAL(triggered()), menuEDDiseases, SLOT(keyUp()));
     QKeyEventTransition *k21 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Left);
     stateEDDiseases->addTransition(k21);
     connect(k21, SIGNAL(triggered()), menuEDDiseases, SLOT(keyLeft()));
     QKeyEventTransition *k22 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Right);
     stateEDDiseases->addTransition(k22);
     connect(k22, SIGNAL(triggered()), menuEDDiseases, SLOT(keyRight()));
     QKeyEventTransition *k23 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Escape);
     k23->setTargetState(stateGameSettings);
     stateEDDiseases->addTransition(k23);


     stateNetworkGameMenu->assignProperty(menuMain, "pos", QPointF(-(scene->width()/2 + menuMain->boundingRect().width()/2),0));
     stateNetworkGameMenu->assignProperty(menuNetworkGame, "pos", QPointF(0,0));
//     stateNetworkGameMenu->assignProperty(menuGameSettings, "pos", QPointF(scene->width()/2 + menuGameSettings->boundingRect().width()/2,0));
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu1Selected()), stateLocalGameMenu);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu2Selected()), stateNetworkGameMenu);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu3Selected()), stateOptionsMenu);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu4Selected()), stateMapEditor);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu5Selected()), stateAbout);
//     stateMainMenu->addTransition(menuMain, SIGNAL(menu6Selected()), finalState);
     QKeyEventTransition *k24 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Down);
     stateNetworkGameMenu->addTransition(k24);
     connect(k24, SIGNAL(triggered()), menuNetworkGame, SLOT(keyDown()));
     QKeyEventTransition *k25 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Up);
     stateNetworkGameMenu->addTransition(k25);
     connect(k25, SIGNAL(triggered()), menuNetworkGame, SLOT(keyUp()));
     QKeyEventTransition *k26 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Escape);
     k26->setTargetState(stateMainMenu);
     stateNetworkGameMenu->addTransition(k26);
     QKeyEventTransition *k27 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Return);
     stateNetworkGameMenu->addTransition(k27);
     connect(k27, SIGNAL(triggered()), menuNetworkGame, SLOT(keyEnter()));


     stateOptionsMenu->assignProperty(menuMain, "pos", QPointF(-(scene->width()/2 + menuGameSettings->boundingRect().width()/2),0));
     stateOptionsMenu->assignProperty(menuOptions, "pos", QPointF(0,0));
     QKeyEventTransition *k29 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Down);
     stateOptionsMenu->addTransition(k29);
     connect(k29, SIGNAL(triggered()), menuOptions, SLOT(keyDown()));
     QKeyEventTransition *k30 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Up);
     stateOptionsMenu->addTransition(k30);
     connect(k30, SIGNAL(triggered()), menuOptions, SLOT(keyUp()));
     QKeyEventTransition *k31 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Left);
     stateOptionsMenu->addTransition(k31);
     connect(k31, SIGNAL(triggered()), menuOptions, SLOT(keyLeft()));
     QKeyEventTransition *k32 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Right);
     stateOptionsMenu->addTransition(k32);
     connect(k32, SIGNAL(triggered()), menuOptions, SLOT(keyRight()));
     QKeyEventTransition *k33 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Escape);
     k33->setTargetState(stateMainMenu);
     stateOptionsMenu->addTransition(k33);


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

void QArawnWindow::closeEvent(QCloseEvent *event)
{
    //ArawnSettings::instance()->save();
    event->accept();
}




