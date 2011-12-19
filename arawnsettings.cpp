#include "arawnheader.h"

ArawnSettings::ArawnSettings()
{
    languageValues.push_back(QPair("English", 0));
    languageValues.push_back(QPair("Magyar", 1));
    openGlRenderingValues.push_back(QPair("Yes", true));
    openGlRenderingValues.push_back(QPair("No", false));
    showCorpsePartsValues.push_back(QPair("Yes", true));
    showCorpsePartsValues.push_back(QPair("No", false));
    shakyExplosionValues.push_back(QPair("Yes", true));
    shakyExplosionValues.push_back(QPair("No", false));
    roundTimeDefaultValues.push_back(QPair("30", 30));
    roundTimeDefaultValues.push_back(QPair("45", 45));
    roundTimeDefaultValues.push_back(QPair("60", 60));
    roundTimeDefaultValues.push_back(QPair("90", 90));
    roundTimeDefaultValues.push_back(QPair("120", 120));
    roundTimeDefaultValues.push_back(QPair("180", 180));
    roundTimeDefaultValues.push_back(QPair("240", 240));
    startBombsValues.push_back(QPair("1", 1));
    startBombsValues.push_back(QPair("2", 2));
    startBombsValues.push_back(QPair("3", 3));
    startBombsValues.push_back(QPair("4", 4));
    startBombsValues.push_back(QPair("5", 5));
    startBombsValues.push_back(QPair("6", 6));
    startBombsValues.push_back(QPair("7", 7));
    startBombsValues.push_back(QPair("8", 8));
    startBombsValues.push_back(QPair("9", 9));
    startBombsValues.push_back(QPair("10", 10));
    startBombsValues.push_back(QPair("11", 11));
    startBombsValues.push_back(QPair("12", 12));
    startBombsValues.push_back(QPair("13", 13));
    startBombsValues.push_back(QPair("14", 14));
    startBombsValues.push_back(QPair("15", 15));
    maxBombsValues.push_back(QPair("1", 1));
    maxBombsValues.push_back(QPair("2", 2));
    maxBombsValues.push_back(QPair("3", 3));
    maxBombsValues.push_back(QPair("4", 4));
    maxBombsValues.push_back(QPair("5", 5));
    maxBombsValues.push_back(QPair("6", 6));
    maxBombsValues.push_back(QPair("7", 7));
    maxBombsValues.push_back(QPair("8", 8));
    maxBombsValues.push_back(QPair("9", 9));
    maxBombsValues.push_back(QPair("10", 10));
    maxBombsValues.push_back(QPair("11", 11));
    maxBombsValues.push_back(QPair("12", 12));
    maxBombsValues.push_back(QPair("13", 13));
    maxBombsValues.push_back(QPair("14", 14));
    maxBombsValues.push_back(QPair("15", 15));
    startFireValues.push_back(QPair("1", 1));
    startFireValues.push_back(QPair("2", 2));
    startFireValues.push_back(QPair("3", 3));
    startFireValues.push_back(QPair("4", 4));
    startFireValues.push_back(QPair("5", 5));
    startFireValues.push_back(QPair("6", 6));
    startFireValues.push_back(QPair("7", 7));
    startFireValues.push_back(QPair("8", 8));
    startFireValues.push_back(QPair("9", 9));
    startFireValues.push_back(QPair("10", 10));
    startFireValues.push_back(QPair("11", 11));
    startFireValues.push_back(QPair("12", 12));
    startFireValues.push_back(QPair("13", 13));
    startFireValues.push_back(QPair("14", 14));
    startFireValues.push_back(QPair("15", 15));
    maxFireValues.push_back(QPair("1", 1));
    maxFireValues.push_back(QPair("2", 2));
    maxFireValues.push_back(QPair("3", 3));
    maxFireValues.push_back(QPair("4", 4));
    maxFireValues.push_back(QPair("5", 5));
    maxFireValues.push_back(QPair("6", 6));
    maxFireValues.push_back(QPair("7", 7));
    maxFireValues.push_back(QPair("8", 8));
    maxFireValues.push_back(QPair("9", 9));
    maxFireValues.push_back(QPair("10", 10));
    maxFireValues.push_back(QPair("11", 11));
    maxFireValues.push_back(QPair("12", 12));
    maxFireValues.push_back(QPair("13", 13));
    maxFireValues.push_back(QPair("14", 14));
    maxFireValues.push_back(QPair("15", 15));
    startSpeedValues.push_back(QPair("1", 1));
    startSpeedValues.push_back(QPair("2", 2));
    startSpeedValues.push_back(QPair("3", 3));
    startSpeedValues.push_back(QPair("4", 4));
    startSpeedValues.push_back(QPair("5", 5));
    startSpeedValues.push_back(QPair("6", 6));
    startSpeedValues.push_back(QPair("7", 7));
    startSpeedValues.push_back(QPair("8", 8));
    startSpeedValues.push_back(QPair("9", 9));
    startSpeedValues.push_back(QPair("10", 10));
    startSpeedValues.push_back(QPair("11", 11));
    startSpeedValues.push_back(QPair("12", 12));
    startSpeedValues.push_back(QPair("13", 13));
    startSpeedValues.push_back(QPair("14", 14));
    startSpeedValues.push_back(QPair("15", 15));
    maxSpeedValues.push_back(QPair("1", 1));
    maxSpeedValues.push_back(QPair("2", 2));
    maxSpeedValues.push_back(QPair("3", 3));
    maxSpeedValues.push_back(QPair("4", 4));
    maxSpeedValues.push_back(QPair("5", 5));
    maxSpeedValues.push_back(QPair("6", 6));
    maxSpeedValues.push_back(QPair("7", 7));
    maxSpeedValues.push_back(QPair("8", 8));
    maxSpeedValues.push_back(QPair("9", 9));
    maxSpeedValues.push_back(QPair("10", 10));
    maxSpeedValues.push_back(QPair("11", 11));
    maxSpeedValues.push_back(QPair("12", 12));
    maxSpeedValues.push_back(QPair("13", 13));
    maxSpeedValues.push_back(QPair("14", 14));
    maxSpeedValues.push_back(QPair("15", 15));
    startPushBombsValues.push_back(QPair("Yes", true));
    startPushBombsValues.push_back(QPair("No", false));
    enablePushBombsValues.push_back(QPair("Yes", true));
    enablePushBombsValues.push_back(QPair("No", false));
    startDropBombsValues.push_back(QPair("Yes", true));
    startDropBombsValues.push_back(QPair("No", false));
    enableDropBombsValues.push_back(QPair("Yes", true));
    enableDropBombsValues.push_back(QPair("No", false));
    enableFailingBombsValues.push_back(QPair("Yes", true));
    enableFailingBombsValues.push_back(QPair("No", false));
    enableOppositeControlsValues.push_back(QPair("Yes", true));
    enableOppositeControlsValues.push_back(QPair("No", false));
    enableInvisibilityValues.push_back(QPair("Yes", true));
    enableInvisibilityValues.push_back(QPair("No", false));
    bombSpeedValues.push_back(QPair("30", 30));
    bombSpeedValues.push_back(QPair("35", 35));
    bombSpeedValues.push_back(QPair("40", 40));
    bombSpeedValues.push_back(QPair("45", 45));
    bombSpeedValues.push_back(QPair("50", 50));
    bombTimerValues.push_back(QPair("10", 10));
    bombTimerValues.push_back(QPair("12", 12));
    bombTimerValues.push_back(QPair("14", 14));
    bombTimerValues.push_back(QPair("12", 12));
    bombTimerValues.push_back(QPair("18", 18));
    bombTimerValues.push_back(QPair("20", 20));
    bombTimerValues.push_back(QPair("22", 22));
    bombTimerValues.push_back(QPair("24", 24));
    bombTimerValues.push_back(QPair("26", 26));
    bombTimerValues.push_back(QPair("28", 28));
    bombTimerValues.push_back(QPair("30", 30));
    bombTimerValues.push_back(QPair("32", 32));
    bombTimerValues.push_back(QPair("34", 34));
    bombTimerValues.push_back(QPair("36", 36));
    bombTimerValues.push_back(QPair("38", 38));
    bombTimerValues.push_back(QPair("40", 40));
    bombTimerValues.push_back(QPair("42", 42));
    bombTimerValues.push_back(QPair("44", 44));
    bombTimerValues.push_back(QPair("46", 46));
    bombTimerValues.push_back(QPair("48", 48));
    bombTimerValues.push_back(QPair("50", 50));
    resolutionValues.push_back(QPair("800x600", QPoint(800, 600)));
    resolutionValues.push_back(QPair("1024x768", QPoint(1024, 768)));
    resolutionValues.push_back(QPair("1024x600", QPoint(1024, 600)));
    resolutionValues.push_back(QPair("1280x720", QPoint(1280, 720)));
    resolutionValues.push_back(QPair("1280x800", QPoint(1280, 800)));
    defaultPlayer1Name = "Nuadha";
    defaultPlayer2Name = "Diarmait";
    defaultPlayer3Name = "Fachtna";
    defaultPlayer4Name = "Pryderi";

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
        sReader >> *this;
        sFile.close();
        return;
    }

    language = 0;
    openGlRendering = false;
    showCorpseParts = true;
    shakyExplosion = true;
    roundTimeDefault = 60;
    startBombs = 1;
    maxBombs = 8;
    startFire = 1;
    maxFire = 8;
    startSpeed = 1;
    maxSpeed = 8;
    startPushBombs = false;
    enablePushBombs = true;
    startDropBombs = false;
    enableDropBombs = true;
    enableFailingBombs = true;
    enableOppositeControls = true;
    enableInvisibility = true;
    bombSpeed = 40;
    bombTimer = 28;

    QRect sr = QApplication::desktop()->screenGeometry();
    if(((float)sr.width())/((float)sr.height()) > 1.7F){
        if(sr.width() >= 1280){
            resolution = QPoint(1280, 720);
        }else{
            resolution = QPoint(1024, 600);
        }
        wideLayout = true;
    }else{
    if(((float)sr.width())/((float)sr.height()) > 1.5F){
        if(sr.width() >= 1280){
            resolution = QPoint(1280, 800);
        }else{
            resolution = QPoint(1024, 600);
        }
        wideLayout = true;
    }else{
    if(((float)sr.width())/((float)sr.height()) < 1.4F){
        if(sr.width() >= 1024){
            resolution = QPoint(1024, 768);
        }else{
            resolution = QPoint(800, 600);
        }
        wideLayout = false;
    }}}


}

QDataStream &ArawnSettings::operator >>(QDataStream &stream)
{
    stream >> language;
    stream >> openGlRendering;
    stream >> showCorpseParts;
    stream >> shakyExplosion;
    stream >> roundTimeDefault;
    stream >> startBombs;
    stream >> maxBombs;
    stream >> startFire.;
    stream >> maxFire;
    stream >> startSpeed;
    stream >> maxSpeed;
    stream >> startPushBombs;
    stream >> enablePushBombs;
    stream >> startDropBombs;
    stream >> enableDropBombs;
    stream >> enableFailingBombs;
    stream >> enableOppositeControls;
    stream >> enableInvisibility;
    stream >> bombSpeed;
    stream >> bombTimer;
    stream >> resolution.toPoint().rx();
    stream >> resolution.toPoint().ry();
    stream >> wideLayout;
    stream >> defaultPlayer1Name;
    stream >> defaultPlayer2Name;
    stream >> defaultPlayer3Name;
    stream >> defaultPlayer4Name;
}

QDataStream &ArawnSettings::operator <<(QDataStream &stream)
{
    stream << language.toInt();
    stream << openGlRendering.toBool();
    stream << showCorpseParts.toBool();
    stream << shakyExplosion.toBool();
    stream << roundTimeDefault.toInt();
    stream << startBombs.toInt();
    stream << maxBombs.toInt();
    stream << startFire.toInt();
    stream << maxFire.toInt();
    stream << startSpeed.toInt();
    stream << maxSpeed.toInt();
    stream << startPushBombs.toBool();
    stream << enablePushBombs.toBool();
    stream << startDropBombs.toBool();
    stream << enableDropBombs.toBool();
    stream << enableFailingBombs.toBool();
    stream << enableOppositeControls.toBool();
    stream << enableInvisibility.toBool();
    stream << bombSpeed.toInt();
    stream << bombTimer.toInt();
    stream << resolution.toPoint().x();
    stream << resolution.toPoint().y();
    stream << wideLayout;
    stream << defaultPlayer1Name.toString();
    stream << defaultPlayer2Name.toString();
    stream << defaultPlayer3Name.toString();
    stream << defaultPlayer4Name.toString();
}

static void ArawnSettings::create()
{
    if(!aSettings){
        aSettings = new ArawnSettings;
    }
}

static ArawnSettings * ArawnSettings::instance()
{
    return aSettings;
}




