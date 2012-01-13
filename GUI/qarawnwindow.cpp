#include "GUI/qarawnwindow.hpp"
#include "GUI/graphicsnetworksettings.hpp"
#include "GUI/graphicsplayersetup.hpp"
#include "CORE/cup.hpp"
#include "GUI/graphicsplayer.hpp"


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
    stateMenu = new QState;
    machine->addState(stateMenu);
    stateMenuHistory = new QHistoryState(stateMenu);
    stateAbout = new QState;
    machine->addState(stateAbout);
    stateGame = new QState;
    machine->addState(stateGame);
    stateNetSettings = new QState;
    machine->addState(stateNetSettings);
    statePlayerSetup = new QState;
    machine->addState(statePlayerSetup);
    stateMapSelection = new QState;
    machine->addState(stateMapSelection);
    stateSurvivalCup = new QState;
    machine->addState(stateSurvivalCup);
    stateMurderCup = new QState;
    machine->addState(stateMurderCup);
    roomState = new QState;
    machine->addState(roomState);
    stateNetPlayerSetup = new QState;
    machine->addState(stateNetPlayerSetup);
    stateNetSurvivalCup = new QState;
    machine->addState(stateNetSurvivalCup);
    connect(stateNetSurvivalCup, SIGNAL(entered()), this, SLOT(startSurvival()));
    stateNetMurderCup = new QState;
    machine->addState(stateNetMurderCup);
    connect(stateNetMurderCup, SIGNAL(entered()), this, SLOT(startMurder()));
    stateQuit = new QState;
    machine->addState(stateQuit);

    finalState = new QFinalState;
    machine->addState(finalState);

    mapState = new QState(stateGame);
    cupState = new QState(stateGame);
    gameFinal = new QFinalState(stateGame);
    stateGame->setInitialState(mapState);
    stateGame->addTransition(stateGame, SIGNAL(finished()), stateMenuHistory);
    connect(stateGame, SIGNAL(entered()), this, SLOT(enterGame()));
    connect(stateGame, SIGNAL(finished()), this, SLOT(finishGame()));

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

    stateArawn->addTransition(timerStArawnToStMM, SIGNAL(timeout()), stateMenu);

    //Végén
    timerStLogoToStArawn->start(50);
    connect(machine, SIGNAL(finished()), this, SLOT(close()));
}


void QArawnWindow::initializeMenus()
{
     QState* sMainMenu = new QState(stateMenu);
     stateMenu->setInitialState(sMainMenu);
     GraphicsMenu *mainMenu = new GraphicsMenu(tr("Main menu"), 0, sMainMenu, sounds[2], sounds[1], this);

     GraphicsMenu* localMenu = mainMenu->addSubMenu(tr("Local game"));
     GraphicsMenu* networkMenu = mainMenu->addSubMenu(tr("Network game"));
     GraphicsMenu* optionsMenu = mainMenu->addSubMenu(tr("Options"));
     mainMenu->addMenuItem(tr("Credits"), stateAbout);
     mainMenu->addMenuItem(tr("Quit"), stateQuit);

     localMenu->addMenuItem(tr("Player setup"), statePlayerSetup);
     localMenu->addMenuItem(tr("Map selection"), stateMapSelection);
     GraphicsMenu* gameSettingsMenu = localMenu->addSubMenu(tr("Game settings"));
     localMenu->addMenuItem(tr("Start survival cup"), stateSurvivalCup);
     localMenu->addMenuItem(tr("Start murder cup"), stateMurderCup);

     GraphicsMenu* smE = gameSettingsMenu->addSubMenu(tr("Start/max extras"));
     GraphicsMenu* edD = gameSettingsMenu->addSubMenu(tr("Enable diseases"));
     gameSettingsMenu->addOptionItem(tr("Round time"), ArawnSettings::instance()->roundTimeDefault, ArawnSettings::instance()->roundTimeDefaultValues);
     gameSettingsMenu->addOptionItem(tr("Points to win"), ArawnSettings::instance()->pointsToWin, ArawnSettings::instance()->pointsToWinValues);
     gameSettingsMenu->addOptionItem(tr("Bomb timer 1/10 sec"), ArawnSettings::instance()->bombTimer, ArawnSettings::instance()->bombTimerValues);
     gameSettingsMenu->addOptionItem(tr("Bomb speed f/10 sec"), ArawnSettings::instance()->bombSpeed, ArawnSettings::instance()->bombSpeedValues);

     smE->addOptionItem(tr("Start bombs"), ArawnSettings::instance()->startBombs, ArawnSettings::instance()->startBombsValues);
     smE->addOptionItem(tr("Max bombs"), ArawnSettings::instance()->maxBombs, ArawnSettings::instance()->maxBombsValues);
     smE->addOptionItem(tr("Start power"), ArawnSettings::instance()->startFire, ArawnSettings::instance()->startFireValues);
     smE->addOptionItem(tr("Max power"), ArawnSettings::instance()->maxFire, ArawnSettings::instance()->maxFireValues);
     smE->addOptionItem(tr("Start speed"), ArawnSettings::instance()->startSpeed, ArawnSettings::instance()->startSpeedValues);
     smE->addOptionItem(tr("Max speed"), ArawnSettings::instance()->maxSpeed, ArawnSettings::instance()->maxSpeedValues);
     smE->addOptionItem(tr("Start gloves"), ArawnSettings::instance()->startDropBombs, ArawnSettings::instance()->startDropBombsValues);
     smE->addOptionItem(tr("Start boot"), ArawnSettings::instance()->startPushBombs, ArawnSettings::instance()->startPushBombsValues);

     edD->addOptionItem(tr("Failing bombs"), ArawnSettings::instance()->enableFailingBombs, ArawnSettings::instance()->enableFailingBombsValues);
     edD->addOptionItem(tr("Opposite controls"), ArawnSettings::instance()->enableOppositeControls, ArawnSettings::instance()->enableOppositeControlsValues);
     edD->addOptionItem(tr("Invisibility"), ArawnSettings::instance()->enableInvisibility, ArawnSettings::instance()->enableInvisibilityValues);

     GraphicsMenu *createNetworkMenu = networkMenu->addSubMenu(tr("Create network"));
     networkMenu->addMenuItem(tr("Connect"), stateNetSettings);

     createNetworkMenu->addMenuItem(tr("Player setup"), stateNetPlayerSetup);
     createNetworkMenu->addMenuItem(tr("Map selection"), stateMapSelection);
     GraphicsMenu *netGameSettingsMenu = createNetworkMenu->addSubMenu(tr("Game settings"));
     createNetworkMenu->addMenuItem(tr("Start survival cup"), stateNetSurvivalCup);
     createNetworkMenu->addMenuItem(tr("Start murder cup"), stateNetMurderCup);

     GraphicsMenu *NsmE = netGameSettingsMenu->addSubMenu(tr("Start/max extras"));
     GraphicsMenu *NedD = netGameSettingsMenu->addSubMenu(tr("Enable diseases"));
     netGameSettingsMenu->addOptionItem(tr("Round time"), ArawnSettings::instance()->roundTimeDefault, ArawnSettings::instance()->roundTimeDefaultValues);
     netGameSettingsMenu->addOptionItem(tr("Points to win"), ArawnSettings::instance()->pointsToWin, ArawnSettings::instance()->pointsToWinValues);
     netGameSettingsMenu->addOptionItem(tr("Bomb timer 1/10 sec"), ArawnSettings::instance()->bombTimer, ArawnSettings::instance()->bombTimerValues);
     netGameSettingsMenu->addOptionItem(tr("Bomb speed f/10 sec"), ArawnSettings::instance()->bombSpeed, ArawnSettings::instance()->bombSpeedValues);

     NsmE->addOptionItem(tr("Start bombs"), ArawnSettings::instance()->startBombs, ArawnSettings::instance()->startBombsValues);
     NsmE->addOptionItem(tr("Max bombs"), ArawnSettings::instance()->maxBombs, ArawnSettings::instance()->maxBombsValues);
     NsmE->addOptionItem(tr("Start power"), ArawnSettings::instance()->startFire, ArawnSettings::instance()->startFireValues);
     NsmE->addOptionItem(tr("Max power"), ArawnSettings::instance()->maxFire, ArawnSettings::instance()->maxFireValues);
     NsmE->addOptionItem(tr("Start speed"), ArawnSettings::instance()->startSpeed, ArawnSettings::instance()->startSpeedValues);
     NsmE->addOptionItem(tr("Max speed"), ArawnSettings::instance()->maxSpeed, ArawnSettings::instance()->maxSpeedValues);
     NsmE->addOptionItem(tr("Start gloves"), ArawnSettings::instance()->startDropBombs, ArawnSettings::instance()->startDropBombsValues);
     NsmE->addOptionItem(tr("Start boot"), ArawnSettings::instance()->startPushBombs, ArawnSettings::instance()->startPushBombsValues);

     NedD->addOptionItem(tr("Failing bombs"), ArawnSettings::instance()->enableFailingBombs, ArawnSettings::instance()->enableFailingBombsValues);
     NedD->addOptionItem(tr("Opposite controls"), ArawnSettings::instance()->enableOppositeControls, ArawnSettings::instance()->enableOppositeControlsValues);
     NedD->addOptionItem(tr("Invisibility"), ArawnSettings::instance()->enableInvisibility, ArawnSettings::instance()->enableInvisibilityValues);

     optionsMenu->addOptionItem(tr("Corpse parts"), ArawnSettings::instance()->showCorpseParts, ArawnSettings::instance()->showCorpsePartsValues);
     optionsMenu->addOptionItem(tr("Shaky explosion"), ArawnSettings::instance()->shakyExplosion, ArawnSettings::instance()->shakyExplosionValues);
     optionsMenu->addOptionItem(tr("OpenGL"), ArawnSettings::instance()->openGlRendering, ArawnSettings::instance()->openGlRenderingValues);
     optionsMenu->addOptionItem(tr("Animate backgrund"), ArawnSettings::instance()->animateFire, ArawnSettings::instance()->animateFireValues);
     optionsMenu->addOptionItem(tr("Resolution"), ArawnSettings::instance()->resolution, ArawnSettings::instance()->resolutionValues);
     optionsMenu->addOptionItem(tr("Language"), ArawnSettings::instance()->language, ArawnSettings::instance()->languageValues);


     GraphicsAbout *aboutItem = new GraphicsAbout;
     aboutItem->setPos(scene->width()/2 + aboutItem->boundingRect().width()/2,0);
     scene->addItem(aboutItem);
     machine->addDefaultAnimation(new QPropertyAnimation(aboutItem, "pos"));
     stateMenu->assignProperty(aboutItem, "pos", QPointF(scene->width()/2 + aboutItem->boundingRect().width()/2,0));
     stateAbout->assignProperty(aboutItem, "pos", QPointF(0,0));
     QKeyEventTransition *k34 = new QKeyEventTransition(this, QEvent::KeyPress, Qt::Key_Escape);
     k34->setTargetState(stateMenuHistory);
     stateAbout->addTransition(k34);
     connect(stateMenu, SIGNAL(entered()), sounds[0], SLOT(play()));
     connect(stateAbout, SIGNAL(entered()), sounds[0], SLOT(play()));

     stateQuit->assignProperty(mainMenu, "pos", QPointF(scene->width()/2 + mainMenu->boundingRect().width()/2,0));
     connect(stateQuit, SIGNAL(entered()), sounds[0], SLOT(play()));
     stateQuit->addTransition(stateQuit, SIGNAL(propertiesAssigned()), finalState);

     GraphicsNPSetup *npSetup = new GraphicsNPSetup(stateMenuHistory, stateNetPlayerSetup);
     npSetup->setPos(scene->width(),0);
     stateMenu->assignProperty(npSetup, "pos", QPointF(scene->width(),0));
     scene->addItem(npSetup);

     GraphicsPlayerSetup *pSetup = new GraphicsPlayerSetup(stateMenuHistory, statePlayerSetup);
     pSetup->setPos(scene->width(),0);
     stateMenu->assignProperty(pSetup, "pos", QPointF(scene->width(),0));
     scene->addItem(pSetup);

     GraphicsNetworkSettings *netSettingsItem = new GraphicsNetworkSettings(g, stateMenuHistory, stateNetSettings, roomState, stateGame);
     netSettingsItem->setPos(scene->width()/2 + netSettingsItem->boundingRect().width(),0);
     stateMenu->assignProperty(netSettingsItem, "pos", QPointF(scene->width()/2 + netSettingsItem->boundingRect().width(), 0));
     scene->addItem(netSettingsItem);

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
    pixFireItem->setOpacity(0.6);
    firAnim = new QPropertyAnimation(pixFireItem, "opacity", pixFireItem);
    if(ArawnSettings::instance()->animateFire.toBool()){
        firAnim->setLoopCount(-1);
        firAnim->setEasingCurve(QEasingCurve::OutInBounce);
        firAnim->setStartValue(0.4);
        firAnim->setEndValue(0.8);
        firAnim->setDuration(1600);
        firAnim->start();
    }

    copyright = new QGraphicsTextItem("Arawn 0.9a Copyright KliMoQu @ PPKE ITK");
    QFont fnt = qApp->font();
    fnt.setPixelSize(20);
    copyright->setFont(fnt);
    copyright->setOpacity(0.8);
    copyright->setPos(-(scene->width()/2)+5,(scene->height()/2)-30);
    QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect(copyright);
    dse->setColor(QColor(100, 10, 10, 200));
    dse->setOffset(1.5);
    copyright->setGraphicsEffect(dse);
    scene->addItem(copyright);
}

void QArawnWindow::closeEvent(QCloseEvent *event)
{
    ArawnSettings::instance()->save();
    ArawnSettings::deleteInstance();
    event->accept();
}

void QArawnWindow::enterGame()
{
    copyright->setVisible(false);
    pixFireItem->setVisible(false);
    firAnim->stop();

    grMap = new GraphicsMap(g, mapState, cupState);
    grMap->setPos(-400, -230);
    mapState->assignProperty(grMap, "visible", true);
    cupState->assignProperty(grMap, "visible", false);
    scene->addItem(grMap);
    grTimer = new GraphicsTimer;
    grTimer->setPos(-400, -300);
    mapState->assignProperty(grTimer, "visible", true);
    cupState->assignProperty(grTimer, "visible", false);
    scene->addItem(grTimer);
    grCup = new GraphicsCup(g);
    grCup->setPos(0,0);
    scene->addItem(grCup);
    mapState->assignProperty(grCup, "visible", false);
    cupState->assignProperty(grCup, "visible", true);

    mapState->addTransition(g, SIGNAL(GameOver()), cupState);
    cupState->addTransition(g, SIGNAL(GameStarted(int)), mapState);
    connect(g, SIGNAL(GameStarted(int)), grTimer, SLOT(setTimer(int)));
    connect(mapState, SIGNAL(entered()), grMap, SLOT(setGrabKeyboard()));
    connect(mapState, SIGNAL(exited()), grMap, SLOT(setUngrabKeyboard()));

    connect(grMap, SIGNAL(bombBlasted()), sounds[4], SLOT(play()));
    connect(grMap, SIGNAL(bombPlanted()), sounds[3], SLOT(play()));
    connect(grMap, SIGNAL(playerDied()), sounds[6], SLOT(play()));
    connect(grMap, SIGNAL(playerBlasted()), sounds[9], SLOT(play()));

}

void QArawnWindow::finishGame()
{
    grMap->deleteLater();
    grTimer->deleteLater();
    grCup->deleteLater();

    copyright->setVisible(true);
    if(ArawnSettings::instance()->animateFire.toBool()){
        firAnim->setLoopCount(-1);
        firAnim->setEasingCurve(QEasingCurve::OutInBounce);
        firAnim->setStartValue(0.4);
        firAnim->setEndValue(0.8);
        firAnim->setDuration(1600);
        firAnim->start();
    }
}

void QArawnWindow::startSurvival()
{
    g = new Game(aSetInstance->noOfPlayers, aSetInstance->bombTimer.toInt(), aSetInstance, true);
    c = new Cup(aSetInstance);
    g->SetCup(c);

}

void QArawnWindow::startMurder()
{
    g = new Game(aSetInstance->noOfPlayers, aSetInstance->bombTimer.toInt(), aSetInstance, false);
    c = new Cup(aSetInstance);
    g->SetCup(c);
}












