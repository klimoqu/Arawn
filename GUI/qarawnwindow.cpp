#include "arawnheader.h"


QDataStream &operator >>(QDataStream &stream, ArawnSettings &settings)
{
    int v;
    stream >> v;
    stream >> settings.bombSpeed;
    stream >> settings.bombTimer;
    stream >> settings.enableDropBombs;
    stream >> settings.enableFailingBombs;
    stream >> settings.enableInvisibility;
    stream >> settings.enableOppositeControls;
    stream >> settings.enablePushBombs;
    stream >> settings.language;
    stream >> settings.maxMoreBombs;
    stream >> settings.maxMoreFire;
    stream >> settings.maxMoreSpeed;
    stream >> settings.pointsToPlayOff;
    stream >> settings.roundTimeDefault;
    stream >> settings.shakyExplosion;
    stream >> settings.showCorpseParts;
    stream >> settings.startBombs;
    stream >> settings.startDropBombs;
    stream >> settings.startFire;
    stream >> settings.startPushBombs;
    stream >> settings.startSpeed;
    stream >> settings.openGlRendering;
    stream >> settings.screenX;
    stream >> settings.screenY;
    return stream;
}

QDataStream &operator <<(QDataStream &stream, const ArawnSettings &settings)
{
    stream << ArawnSettings::Current;
    stream << settings.bombSpeed;
    stream << settings.bombTimer;
    stream << settings.enableDropBombs;
    stream << settings.enableFailingBombs;
    stream << settings.enableInvisibility;
    stream << settings.enableOppositeControls;
    stream << settings.enablePushBombs;
    stream << settings.language;
    stream << settings.maxMoreBombs;
    stream << settings.maxMoreFire;
    stream << settings.maxMoreSpeed;
    stream << settings.pointsToPlayOff;
    stream << settings.roundTimeDefault;
    stream << settings.shakyExplosion;
    stream << settings.showCorpseParts;
    stream << settings.startBombs;
    stream << settings.startDropBombs;
    stream << settings.startFire;
    stream << settings.startPushBombs;
    stream << settings.startSpeed;
    stream << settings.openGlRendering;
    stream << settings.screenX;
    stream << settings.screenY;
    return stream;
}



void QArawnWindow::initWindow()
{
    // LOAD SAVED DATA
#ifdef Q_OS_WIN
    QDir dir(QDir::homePath() + "/AppData");
    if(!dir.exists("Arawn"))
        dir.mkdir("Arawn");
    path = QDir::homePath() + "/AppData/Arawn/";
#else
    QDir dir(QDir::homePath() + "/.config");
    if(!dir.exists("Arawn"))
        dir.mkdir("Arawn");
    path = QDir::homePath() + "/.config/Arawn/";
#endif
    QRect sr = QApplication::desktop()->screenGeometry();
    if(QFile::exists(path+"gamesettings")){
        QFile sFile(path+"gamesettings");
        sFile.open(QFile::ReadOnly);
        QDataStream sReader(&sFile);
        sReader >> aSettings;
        sFile.close();
    }else{ // TODO törölni a fájlbaírást
//        QFile sFile(path+"gamesettings");
//        sFile.open(QFile::WriteOnly);
//        sFile.close();

        // Képernyőfelbontás ellenőrzése
        aSettings.screenX = sr.width();
        aSettings.screenY = sr.height();
    }
    if ( ((float)aSettings.screenX) / ((float)aSettings.screenY) > 1.5F ) {
        aSettings.wideLayout = true;
    }else{
        aSettings.wideLayout = false;
    }

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::BlankCursor);
    setGeometry(0, 0, aSettings.screenX, aSettings.screenY);
    setFrameStyle(QFrame::NoFrame);
    setRenderHint(QPainter::Antialiasing);
    scale(((qreal)sr.width()) / (qreal)aSettings.screenX,
          ((qreal)sr.height()) / (qreal)aSettings.screenY);


    scene = new QGraphicsScene(-(aSettings.screenX/2), -(aSettings.screenY/2),
                    aSettings.screenX, aSettings.screenY, this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    welcomePixmap = new QGraphicsPixmapItem(QPixmap("res/KliMoQu.png"), 0, scene);
    welcomePixmap->setPos(-260, -190);
    scene->addItem(welcomePixmap);

    setBackgroundBrush(QBrush(Qt::black));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    setScene(scene);
}


void QArawnWindow::initializeOthers()
{
    QFontDatabase::addApplicationFont("res/screenge.ttf");
    QFontDatabase fdb;
    font = fdb.font("Screengem", "Normal", 36);

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
}


void QArawnWindow::showArawnScreen()
{
    scene->removeItem(welcomePixmap);

    QGraphicsPixmapItem *arawnItem = new QGraphicsPixmapItem(
                QPixmap("res/Arawn.png").scaledToHeight(aSettings.screenY, Qt::SmoothTransformation), 0, scene);
    QGraphicsPixmapItem *hiryrv = new QGraphicsPixmapItem(
                QPixmap("res/hiryrvdydd.png").scaledToWidth((3*aSettings.screenX)/4, Qt::SmoothTransformation), 0, scene);

    QGraphicsOpacityEffect *opEffect = new QGraphicsOpacityEffect(this);
    opEffect->setOpacity(0.0);
    QGraphicsOpacityEffect *ohEffect = new QGraphicsOpacityEffect(this);
    ohEffect->setOpacity(0.0);

    arawnItem->setPos(aSettings.screenX/2 - arawnItem->boundingRect().width() , -arawnItem->boundingRect().height()/2);
    hiryrv->setPos(-hiryrv->boundingRect().width()/2, -hiryrv->boundingRect().height()/2);

    arawnItem->setGraphicsEffect(opEffect);
    hiryrv->setGraphicsEffect(ohEffect);

    QPropertyAnimation *aanim = new QPropertyAnimation(opEffect, "opacity", this);
    aanim->setStartValue(0.0);
    aanim->setEndValue(0.6);
    aanim->setDuration(1000);
    QPropertyAnimation *hanim = new QPropertyAnimation(ohEffect, "opacity", this);
    hanim->setStartValue(0.0);
    hanim->setEndValue(0.9);
    hanim->setDuration(700);

    scene->addItem(arawnItem);
    scene->addItem(hiryrv);

    aanim->start(QAbstractAnimation::DeleteWhenStopped);
    hanim->start(QAbstractAnimation::DeleteWhenStopped);

    playSound(14);
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










