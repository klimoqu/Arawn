#include "arawnheader.h"


void QArawnWindow::initWindow()
{

    QRect sr = QApplication::desktop()->screenGeometry();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::BlankCursor);
//    setGeometry(0, 0, ArawnSettings::instance().screenX, ArawnSettings::instance().screenY);
    setFrameStyle(QFrame::NoFrame);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scale(((qreal)sr.width()) / (qreal)ArawnSettings::instance()->resolution.toPoint().x(),
          ((qreal)sr.height()) / (qreal)ArawnSettings::instance()->resolution.toPoint().y());


    scene = new QGraphicsScene(-(ArawnSettings::instance()->resolution.toPoint().x()/2),
                               -(ArawnSettings::instance()->resolution.toPoint().y()/2),
                               ArawnSettings::instance()->resolution.toPoint().x(),
                               ArawnSettings::instance()->resolution.toPoint().y(), this);
    scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    pixWelcomeItem = new QGraphicsPixmapItem(QPixmap("res/KliMoQu.png"), 0, scene);
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

    pixFireItem = new QGraphicsPixmapItem(
                QPixmap("res/fire.jpg").scaled(scene->width(),scene->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation), 0, scene);
    pixArawnItem = new QGraphicsPixmapItem(
                QPixmap("res/Arawn.png").scaledToHeight(scene->height(), Qt::SmoothTransformation), 0, scene);
    pixHirItem = new QGraphicsPixmapItem(
                QPixmap("res/hiryrvdydd.png").scaledToWidth((3*scene->width())/4, Qt::SmoothTransformation), 0, scene);

    QGraphicsOpacityEffect *opEffectA = new QGraphicsOpacityEffect(this);
        opEffectA->setOpacity(0.0);
    QGraphicsOpacityEffect *opEffectH = new QGraphicsOpacityEffect(this);
        opEffectH->setOpacity(0.0);
    QGraphicsOpacityEffect *opEffectF = new QGraphicsOpacityEffect(this);
        opEffectF->setOpacity(0.0);

        pixArawnItem->setPos(scene->width()/2 - (pixArawnItem->boundingRect().width()) , -(pixArawnItem->boundingRect().height()/2));
        pixHirItem->setPos(- (pixHirItem->boundingRect().width()/2), - (pixHirItem->boundingRect().height()/2));
        //pixFireItem->setPos(-( pixFireItem->boundingRect()/2), 0);

    pixArawnItem->setGraphicsEffect(opEffectA);
    pixHirItem->setGraphicsEffect(opEffectH);
    pixFireItem->setGraphicsEffect(opEffectF);

    QPropertyAnimation *aanim = new QPropertyAnimation(opEffectA, "opacity", this);
        aanim->setStartValue(0.0);
        aanim->setEndValue(0.6);
        aanim->setDuration(1000);
    QPropertyAnimation *hanim = new QPropertyAnimation(opEffectH, "opacity", this);
        hanim->setStartValue(0.0);
        hanim->setEndValue(0.9);
        hanim->setDuration(700);
    QPropertyAnimation *fanim = new QPropertyAnimation(opEffectH, "opacity", this);
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

}

void QArawnWindow::showMainMenu()
{

}










