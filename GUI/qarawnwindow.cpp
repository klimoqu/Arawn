#include "qarawnwindow.hpp"


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


    welcomeScene = new QGraphicsScene(-260, -190, 520, 380, this);
    welcomeScene->setItemIndexMethod(QGraphicsScene::NoIndex);

    welcomePixmap = new QGraphicsPixmapItem(QPixmap("res/KliMoQu.png"));
    welcomePixmap->setPos(-260, -190);
    welcomeScene->addItem(welcomePixmap);

    setBackgroundBrush(QBrush(Qt::black));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    setScene(welcomeScene);
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
    welcomeSound = new QSound("res/arawn.wav");
    arawnScene = new QGraphicsScene(this);
    arawnScene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // Soundok inicializálása (mert lassú)
}














