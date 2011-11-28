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
    stream >> settings.resolution;
    stream >> settings.roundTimeDefault;
    stream >> settings.shakyExplosion;
    stream >> settings.showCorpseParts;
    stream >> settings.startBombs;
    stream >> settings.startDropBombs;
    stream >> settings.startFire;
    stream >> settings.startPushBombs;
    stream >> settings.startSpeed;
    stream >> settings.openGlRendering;
//    if(v > 1){    }
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
    stream << settings.resolution;
    stream << settings.roundTimeDefault;
    stream << settings.shakyExplosion;
    stream << settings.showCorpseParts;
    stream << settings.startBombs;
    stream << settings.startDropBombs;
    stream << settings.startFire;
    stream << settings.startPushBombs;
    stream << settings.startSpeed;
    stream << settings.openGlRendering;
    return stream;
}


QArawnWindow::QArawnWindow()
{
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
    if(QFile::exists(path+"gamesettings")){
        QFile sFile(path+"gamesettings");
        sFile.open(QFile::ReadOnly);
        QDataStream sReader(&sFile);
        sReader >> aSettings;
        sFile.close();
    }else{ // TODO törölni a fájlbaírást
        QFile sFile(path+"gamesettings");
        sFile.open(QFile::WriteOnly);
        QDataStream sWriter(&sFile);
        sWriter << aSettings;
        sFile.close();

        // Képernyőfelbontás ellenőrzése
        QRect sr = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
        // QApplication::desktop()->setGeometry(); Nem itt kell, és lehet, hogy egyáltalán nem.
        if( ((float)sr.width()) / ((float)sr.height()) > 1.7F ){
            // 16:9
            aSettings.resolution = ArawnSettings::R1280x720;
        }else if ( ((float)sr.width()) / ((float)sr.height()) > 1.55F ) {
            // 16:10
            aSettings.resolution = ArawnSettings::R1280x800;
        }else{
            // 4:3
            aSettings.resolution = ArawnSettings::R1024x768;
        }
    }

    aSettings.wideLayout = true;

    switch(aSettings.resolution){
    case ArawnSettings::R800x600:
        aSettings.screenX = 800;
        aSettings.screenY = 600;
        aSettings.wideLayout = false;
        break;
    case ArawnSettings::R1024x768:
        aSettings.screenX = 1024;
        aSettings.screenY = 768;
        aSettings.wideLayout = false;
        break;
    case ArawnSettings::R1280x1024:
        aSettings.screenX = 1280;
        aSettings.screenY = 1024;
        aSettings.wideLayout = false;
        break;
    case ArawnSettings::R1280x800:
        aSettings.screenX = 1280;
        aSettings.screenY = 800;
        break;
    case ArawnSettings::R1440x900:
        aSettings.screenX = 1440;
        aSettings.screenY = 900;
        break;
    case ArawnSettings::R1680x1050:
        aSettings.screenX = 1680;
        aSettings.screenY = 1050;
        break;
    case ArawnSettings::R1280x720:
        aSettings.screenX = 1280;
        aSettings.screenY = 720;
        break;
    case ArawnSettings::R1366x768:
    default:
        aSettings.screenX = 1366;
        aSettings.screenY = 768;
        break;
    }


    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::BlankCursor);
    setGeometry(0, 0, aSettings.screenX, aSettings.screenY);
    setMinimumSize(aSettings.screenX, aSettings.screenY);
    setMaximumSize(aSettings.screenX, aSettings.screenY);
    setFrameStyle(QFrame::NoFrame);
    //setRenderingSystem();
    setRenderHint(QPainter::Antialiasing);


    scene = new QGraphicsScene(-(aSettings.screenX/2), -(aSettings.screenY/2),
                    aSettings.screenX, aSettings.screenY, this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    welcomePixmap = new QGraphicsPixmapItem(QPixmap("res/KliMoQu.png"));
    welcomePixmap->setPos(-260, -190);
    scene->addItem(welcomePixmap);

    setBackgroundBrush(QBrush(Qt::black));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    setScene(scene);
}

void QArawnWindow::setRenderingSystem()
{
    QWidget *viewport = 0;
    #define QT_NO_OPENGL // TODO következő verzió
    #ifndef QT_NO_OPENGL
    if (aSettings.openGlRendering) {
        QGLWidget *glw = new QGLWidget(QGLFormat(QGL::SampleBuffers));
        glw->setAutoFillBackground(false);
        viewport = glw;
        setCacheMode(QGraphicsView::CacheNone);
    } else // software rendering
    #endif
    {
        // software rendering
        viewport = new QWidget;
        setCacheMode(QGraphicsView::CacheBackground);
    }

    setViewport(viewport);
}


void QArawnWindow::initializeArawnScreen()
{
    QFontDatabase::addApplicationFont("res/screenge.ttf");
    QFontDatabase fdb;
    font = fdb.font("Screengem", "Normal", 36);

    arawnItem = new QGraphicsArawnItem;
    arawnScene->addItem(arawnItem);


    sounds[0] = new QSound("res/0_tofrommenu.wav");
    sounds[1] = new QSound("res/1_changemenu.wav");
    sounds[2] = new QSound("res/2_step.vaw");
    sounds[3] = new QSound("res/3_putbomb.wav");
    sounds[4] = new QSound("res/4_explode.wav");
    sounds[5] = new QSound("res/5_getextra.wav");
    sounds[6] = new QSound("res/6_die.wav");
    sounds[7] = new QSound("res/7_splash1a.wav");
    sounds[8] = new QSound("res/8_splash2a.wav");
    sounds[9] = new QSound("res/9_corpse_explode.wav");
    sounds[10] = new QSound("res/10_deepfall.wav");
    sounds[11] = new QSound("res/11_hurry_up.wav");
    sounds[12] = new QSound("res/12_time_over.wav");
    sounds[13] = new QSound("res/13_klatsch.wav");
    sounds[14] = new QSound("res/arawn.wav");
}


void QArawnWindow::showArawnScreen()
{
    disconnect(&timer1, SIGNAL(timeout()),this, SLOT(showArawnScreen()));
    setScene(arawnScene);

    connect(&timer2, SIGNAL(timeout()), arawnScene, SLOT(advance()));
    timer2.start(40);

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










