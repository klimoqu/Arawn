#include "arawnheader.h"

ArawnSettings* ArawnSettings::aSettings = 0;

ArawnSettings::ArawnSettings()
{
    languageValues.insert("English", 0);
    languageValues.insert("Magyar", 1);
    openGlRenderingValues.insert("Yes", true);
    openGlRenderingValues.insert("No", false);
    showCorpsePartsValues.insert("Yes", true);
    showCorpsePartsValues.insert("No", false);
    shakyExplosionValues.insert("Yes", true);
    shakyExplosionValues.insert("No", false);
    roundTimeDefaultValues.insert("30", 30);
    roundTimeDefaultValues.insert("45", 45);
    roundTimeDefaultValues.insert("60", 60);
    roundTimeDefaultValues.insert("90", 90);
    roundTimeDefaultValues.insert("120", 120);
    roundTimeDefaultValues.insert("180", 180);
    roundTimeDefaultValues.insert("240", 240);
    startBombsValues.insert("1", 1);
    startBombsValues.insert("2", 2);
    startBombsValues.insert("3", 3);
    startBombsValues.insert("4", 4);
    startBombsValues.insert("5", 5);
    startBombsValues.insert("6", 6);
    startBombsValues.insert("7", 7);
    startBombsValues.insert("8", 8);
    startBombsValues.insert("9", 9);
    startBombsValues.insert("10", 10);
    startBombsValues.insert("11", 11);
    startBombsValues.insert("12", 12);
    startBombsValues.insert("13", 13);
    startBombsValues.insert("14", 14);
    startBombsValues.insert("15", 15);
    maxBombsValues.insert("1", 1);
    maxBombsValues.insert("2", 2);
    maxBombsValues.insert("3", 3);
    maxBombsValues.insert("4", 4);
    maxBombsValues.insert("5", 5);
    maxBombsValues.insert("6", 6);
    maxBombsValues.insert("7", 7);
    maxBombsValues.insert("8", 8);
    maxBombsValues.insert("9", 9);
    maxBombsValues.insert("10", 10);
    maxBombsValues.insert("11", 11);
    maxBombsValues.insert("12", 12);
    maxBombsValues.insert("13", 13);
    maxBombsValues.insert("14", 14);
    maxBombsValues.insert("15", 15);
    startFireValues.insert("1", 1);
    startFireValues.insert("2", 2);
    startFireValues.insert("3", 3);
    startFireValues.insert("4", 4);
    startFireValues.insert("5", 5);
    startFireValues.insert("6", 6);
    startFireValues.insert("7", 7);
    startFireValues.insert("8", 8);
    startFireValues.insert("9", 9);
    startFireValues.insert("10", 10);
    startFireValues.insert("11", 11);
    startFireValues.insert("12", 12);
    startFireValues.insert("13", 13);
    startFireValues.insert("14", 14);
    startFireValues.insert("15", 15);
    maxFireValues.insert("1", 1);
    maxFireValues.insert("2", 2);
    maxFireValues.insert("3", 3);
    maxFireValues.insert("4", 4);
    maxFireValues.insert("5", 5);
    maxFireValues.insert("6", 6);
    maxFireValues.insert("7", 7);
    maxFireValues.insert("8", 8);
    maxFireValues.insert("9", 9);
    maxFireValues.insert("10", 10);
    maxFireValues.insert("11", 11);
    maxFireValues.insert("12", 12);
    maxFireValues.insert("13", 13);
    maxFireValues.insert("14", 14);
    maxFireValues.insert("15", 15);
    startSpeedValues.insert("1", 1);
    startSpeedValues.insert("2", 2);
    startSpeedValues.insert("3", 3);
    startSpeedValues.insert("4", 4);
    startSpeedValues.insert("5", 5);
    startSpeedValues.insert("6", 6);
    startSpeedValues.insert("7", 7);
    startSpeedValues.insert("8", 8);
    startSpeedValues.insert("9", 9);
    startSpeedValues.insert("10", 10);
    startSpeedValues.insert("11", 11);
    startSpeedValues.insert("12", 12);
    startSpeedValues.insert("13", 13);
    startSpeedValues.insert("14", 14);
    startSpeedValues.insert("15", 15);
    maxSpeedValues.insert("1", 1);
    maxSpeedValues.insert("2", 2);
    maxSpeedValues.insert("3", 3);
    maxSpeedValues.insert("4", 4);
    maxSpeedValues.insert("5", 5);
    maxSpeedValues.insert("6", 6);
    maxSpeedValues.insert("7", 7);
    maxSpeedValues.insert("8", 8);
    maxSpeedValues.insert("9", 9);
    maxSpeedValues.insert("10", 10);
    maxSpeedValues.insert("11", 11);
    maxSpeedValues.insert("12", 12);
    maxSpeedValues.insert("13", 13);
    maxSpeedValues.insert("14", 14);
    maxSpeedValues.insert("15", 15);
    startPushBombsValues.insert("Yes", true);
    startPushBombsValues.insert("No", false);
    enablePushBombsValues.insert("Yes", true);
    enablePushBombsValues.insert("No", false);
    startDropBombsValues.insert("Yes", true);
    startDropBombsValues.insert("No", false);
    enableDropBombsValues.insert("Yes", true);
    enableDropBombsValues.insert("No", false);
    enableFailingBombsValues.insert("Yes", true);
    enableFailingBombsValues.insert("No", false);
    enableOppositeControlsValues.insert("Yes", true);
    enableOppositeControlsValues.insert("No", false);
    enableInvisibilityValues.insert("Yes", true);
    enableInvisibilityValues.insert("No", false);
    bombSpeedValues.insert("30", 30);
    bombSpeedValues.insert("35", 35);
    bombSpeedValues.insert("40", 40);
    bombSpeedValues.insert("45", 45);
    bombSpeedValues.insert("50", 50);
    bombTimerValues.insert("10", 10);
    bombTimerValues.insert("12", 12);
    bombTimerValues.insert("14", 14);
    bombTimerValues.insert("12", 12);
    bombTimerValues.insert("18", 18);
    bombTimerValues.insert("20", 20);
    bombTimerValues.insert("22", 22);
    bombTimerValues.insert("24", 24);
    bombTimerValues.insert("26", 26);
    bombTimerValues.insert("28", 28);
    bombTimerValues.insert("30", 30);
    bombTimerValues.insert("32", 32);
    bombTimerValues.insert("34", 34);
    bombTimerValues.insert("36", 36);
    bombTimerValues.insert("38", 38);
    bombTimerValues.insert("40", 40);
    bombTimerValues.insert("42", 42);
    bombTimerValues.insert("44", 44);
    bombTimerValues.insert("46", 46);
    bombTimerValues.insert("48", 48);
    bombTimerValues.insert("50", 50);
    resolutionValues.insert("800x600", QPoint(800, 600));
    resolutionValues.insert("1024x768", QPoint(1024, 768));
    resolutionValues.insert("1024x600", QPoint(1024, 600));
    resolutionValues.insert("1280x720", QPoint(1280, 720));
    resolutionValues.insert("1280x800", QPoint(1280, 800));
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
        load(sReader);
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

void ArawnSettings::load(QDataStream &stream)
{
    stream >> language;
    stream >> openGlRendering;
    stream >> showCorpseParts;
    stream >> shakyExplosion;
    stream >> roundTimeDefault;
    stream >> startBombs;
    stream >> maxBombs;
    stream >> startFire;
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

void ArawnSettings::save(QDataStream &stream)
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




