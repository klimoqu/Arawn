#include "arawnheader.h"

ArawnSettings* ArawnSettings::aSettings = 0;

ArawnSettings::ArawnSettings()
{
    languageValues.insert(tr("English"), 0);
    languageValues.insert(tr("Magyar"), 1);
    openGlRenderingValues.insert(tr("Yes"), true);
    openGlRenderingValues.insert(tr("No"), false);
    showCorpsePartsValues.insert(tr("Yes"), true);
    showCorpsePartsValues.insert(tr("No"), false);
    shakyExplosionValues.insert(tr("Yes"), true);
    shakyExplosionValues.insert(tr("No"), false);
    roundTimeDefaultValues.insert(tr("30"), 30);
    roundTimeDefaultValues.insert(tr("45"), 45);
    roundTimeDefaultValues.insert(tr("60"), 60);
    roundTimeDefaultValues.insert(tr("90"), 90);
    roundTimeDefaultValues.insert(tr("120"), 120);
    roundTimeDefaultValues.insert(tr("180"), 180);
    roundTimeDefaultValues.insert(tr("240"), 240);
    pointsToWinValues.insert(tr("1"), 1);
    pointsToWinValues.insert(tr("2"), 2);
    pointsToWinValues.insert(tr("3"), 3);
    pointsToWinValues.insert(tr("4"), 4);
    pointsToWinValues.insert(tr("5"), 5);
    pointsToWinValues.insert(tr("6"), 6);
    pointsToWinValues.insert(tr("7"), 7);
    pointsToWinValues.insert(tr("8"), 8);
    pointsToWinValues.insert(tr("9"), 9);
    pointsToWinValues.insert(tr("10"), 10);
    pointsToWinValues.insert(tr("11"), 11);
    pointsToWinValues.insert(tr("12"), 12);
    pointsToWinValues.insert(tr("13"), 13);
    pointsToWinValues.insert(tr("14"), 14);
    pointsToWinValues.insert(tr("15"), 15);
    startBombsValues.insert(tr("1"), 1);
    startBombsValues.insert(tr("2"), 2);
    startBombsValues.insert(tr("3"), 3);
    startBombsValues.insert(tr("4"), 4);
    startBombsValues.insert(tr("5"), 5);
    startBombsValues.insert(tr("6"), 6);
    startBombsValues.insert(tr("7"), 7);
    startBombsValues.insert(tr("8"), 8);
    startBombsValues.insert(tr("9"), 9);
    startBombsValues.insert(tr("10"), 10);
    startBombsValues.insert(tr("11"), 11);
    startBombsValues.insert(tr("12"), 12);
    startBombsValues.insert(tr("13"), 13);
    startBombsValues.insert(tr("14"), 14);
    startBombsValues.insert(tr("15"), 15);
    maxBombsValues.insert(tr("1"), 1);
    maxBombsValues.insert(tr("2"), 2);
    maxBombsValues.insert(tr("3"), 3);
    maxBombsValues.insert(tr("4"), 4);
    maxBombsValues.insert(tr("5"), 5);
    maxBombsValues.insert(tr("6"), 6);
    maxBombsValues.insert(tr("7"), 7);
    maxBombsValues.insert(tr("8"), 8);
    maxBombsValues.insert(tr("9"), 9);
    maxBombsValues.insert(tr("10"), 10);
    maxBombsValues.insert(tr("11"), 11);
    maxBombsValues.insert(tr("12"), 12);
    maxBombsValues.insert(tr("13"), 13);
    maxBombsValues.insert(tr("14"), 14);
    maxBombsValues.insert(tr("15"), 15);
    startFireValues.insert(tr("1"), 1);
    startFireValues.insert(tr("2"), 2);
    startFireValues.insert(tr("3"), 3);
    startFireValues.insert(tr("4"), 4);
    startFireValues.insert(tr("5"), 5);
    startFireValues.insert(tr("6"), 6);
    startFireValues.insert(tr("7"), 7);
    startFireValues.insert(tr("8"), 8);
    startFireValues.insert(tr("9"), 9);
    startFireValues.insert(tr("10"), 10);
    startFireValues.insert(tr("11"), 11);
    startFireValues.insert(tr("12"), 12);
    startFireValues.insert(tr("13"), 13);
    startFireValues.insert(tr("14"), 14);
    startFireValues.insert(tr("15"), 15);
    maxFireValues.insert(tr("1"), 1);
    maxFireValues.insert(tr("2"), 2);
    maxFireValues.insert(tr("3"), 3);
    maxFireValues.insert(tr("4"), 4);
    maxFireValues.insert(tr("5"), 5);
    maxFireValues.insert(tr("6"), 6);
    maxFireValues.insert(tr("7"), 7);
    maxFireValues.insert(tr("8"), 8);
    maxFireValues.insert(tr("9"), 9);
    maxFireValues.insert(tr("10"), 10);
    maxFireValues.insert(tr("11"), 11);
    maxFireValues.insert(tr("12"), 12);
    maxFireValues.insert(tr("13"), 13);
    maxFireValues.insert(tr("14"), 14);
    maxFireValues.insert(tr("15"), 15);
    startSpeedValues.insert(tr("1"), 1);
    startSpeedValues.insert(tr("2"), 2);
    startSpeedValues.insert(tr("3"), 3);
    startSpeedValues.insert(tr("4"), 4);
    startSpeedValues.insert(tr("5"), 5);
    startSpeedValues.insert(tr("6"), 6);
    startSpeedValues.insert(tr("7"), 7);
    startSpeedValues.insert(tr("8"), 8);
    startSpeedValues.insert(tr("9"), 9);
    startSpeedValues.insert(tr("10"), 10);
    startSpeedValues.insert(tr("11"), 11);
    startSpeedValues.insert(tr("12"), 12);
    startSpeedValues.insert(tr("13"), 13);
    startSpeedValues.insert(tr("14"), 14);
    startSpeedValues.insert(tr("15"), 15);
    maxSpeedValues.insert(tr("1"), 1);
    maxSpeedValues.insert(tr("2"), 2);
    maxSpeedValues.insert(tr("3"), 3);
    maxSpeedValues.insert(tr("4"), 4);
    maxSpeedValues.insert(tr("5"), 5);
    maxSpeedValues.insert(tr("6"), 6);
    maxSpeedValues.insert(tr("7"), 7);
    maxSpeedValues.insert(tr("8"), 8);
    maxSpeedValues.insert(tr("9"), 9);
    maxSpeedValues.insert(tr("10"), 10);
    maxSpeedValues.insert(tr("11"), 11);
    maxSpeedValues.insert(tr("12"), 12);
    maxSpeedValues.insert(tr("13"), 13);
    maxSpeedValues.insert(tr("14"), 14);
    maxSpeedValues.insert(tr("15"), 15);
    startPushBombsValues.insert(tr("Yes"), true);
    startPushBombsValues.insert(tr("No"), false);
    enablePushBombsValues.insert(tr("Yes"), true);
    enablePushBombsValues.insert(tr("No"), false);
    startDropBombsValues.insert(tr("Yes"), true);
    startDropBombsValues.insert(tr("No"), false);
    enableDropBombsValues.insert(tr("Yes"), true);
    enableDropBombsValues.insert(tr("No"), false);
    enableFailingBombsValues.insert(tr("Yes"), true);
    enableFailingBombsValues.insert(tr("No"), false);
    enableOppositeControlsValues.insert(tr("Yes"), true);
    enableOppositeControlsValues.insert(tr("No"), false);
    enableInvisibilityValues.insert(tr("Yes"), true);
    enableInvisibilityValues.insert(tr("No"), false);
    bombSpeedValues.insert(tr("30"), 30);
    bombSpeedValues.insert(tr("35"), 35);
    bombSpeedValues.insert(tr("40"), 40);
    bombSpeedValues.insert(tr("45"), 45);
    bombSpeedValues.insert(tr("50"), 50);
    bombTimerValues.insert(tr("10"), 10);
    bombTimerValues.insert(tr("12"), 12);
    bombTimerValues.insert(tr("14"), 14);
    bombTimerValues.insert(tr("12"), 12);
    bombTimerValues.insert(tr("18"), 18);
    bombTimerValues.insert(tr("20"), 20);
    bombTimerValues.insert(tr("22"), 22);
    bombTimerValues.insert(tr("24"), 24);
    bombTimerValues.insert(tr("26"), 26);
    bombTimerValues.insert(tr("28"), 28);
    bombTimerValues.insert(tr("30"), 30);
    bombTimerValues.insert(tr("32"), 32);
    bombTimerValues.insert(tr("34"), 34);
    bombTimerValues.insert(tr("36"), 36);
    bombTimerValues.insert(tr("38"), 38);
    bombTimerValues.insert(tr("40"), 40);
    bombTimerValues.insert(tr("42"), 42);
    bombTimerValues.insert(tr("44"), 44);
    bombTimerValues.insert(tr("46"), 46);
    bombTimerValues.insert(tr("48"), 48);
    bombTimerValues.insert(tr("50"), 50);
    resolutionValues.insert(tr("800x600"), QPoint(800, 600));
    resolutionValues.insert(tr("1024x768"), QPoint(1024, 768));
    resolutionValues.insert(tr("1024x600"), QPoint(1024, 600));
    resolutionValues.insert(tr("1280x720"), QPoint(1280, 720));
    resolutionValues.insert(tr("1280x800"), QPoint(1280, 800));
    animateFireValues.insert(tr("Yes"), true);
    animateFireValues.insert(tr("No"), false);
    colorValues.insert(tr("Red"), RED);
    colorValues.insert(tr("Blue"), BLUE);
    colorValues.insert(tr("Cyan"), CYAN);
    colorValues.insert(tr("Green"), GREEN);
    colorValues.insert(tr("Purple"), PURPLE);
    colorValues.insert(tr("Yellow"), YELLOW);

    // LOAD SAVED DATA
    if(load())
        return;

    language = 0;
    openGlRendering = false;
    showCorpseParts = true;
    shakyExplosion = true;
    roundTimeDefault = 60;
    pointsToWin = 5;
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
    animateFire = true;
    defaultPlayer1Name = "Nuadha";
    defaultPlayer2Name = "Diarmait";
    defaultPlayer3Name = "Fachtna";
    defaultPlayer4Name = "Pryderi";
    defaultColor = RED;
    defaultIPAddress = "192.168.0.1";

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

bool ArawnSettings::load()
{
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
        QDataStream stream(&sFile);
            stream >> language;
            stream >> openGlRendering;
            stream >> showCorpseParts;
            stream >> shakyExplosion;
            stream >> roundTimeDefault;
            stream >> pointsToWin;
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
            stream >> animateFire;
            stream >> wideLayout;
            stream >> defaultPlayer1Name;
            stream >> defaultPlayer2Name;
            stream >> defaultPlayer3Name;
            stream >> defaultPlayer4Name;
            stream >> defaultColor;
            stream >> defaultIPAddress;
        sFile.close();
        return true;
    }
    return false;
}

void ArawnSettings::save()
{
    QFile sFile(path+"gamesettings");
    sFile.open(QFile::WriteOnly);
    QDataStream stream(&sFile);
        stream << language.toInt();
        stream << openGlRendering.toBool();
        stream << showCorpseParts.toBool();
        stream << shakyExplosion.toBool();
        stream << roundTimeDefault.toInt();
        stream << pointsToWin.toInt();
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
        stream << animateFire.toBool();
        stream << wideLayout;
        stream << defaultPlayer1Name.toString();
        stream << defaultPlayer2Name.toString();
        stream << defaultPlayer3Name.toString();
        stream << defaultPlayer4Name.toString();
        stream << defaultColor.toInt();
        stream << defaultIPAddress.toString();
    sFile.close();
}




