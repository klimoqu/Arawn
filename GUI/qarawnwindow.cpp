#include "qarawnwindow.hpp"


QDataStream &operator >>(QDataStream &stream, ArawnSettings &settings)
{
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
    return stream;
}

QDataStream &operator <<(QDataStream &stream, const ArawnSettings &settings)
{
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
    }else{
        QFile sFile(path+"gamesettings");
        sFile.open(QFile::WriteOnly);
        QDataStream sWriter(&sFile);
        sWriter << aSettings;
        sFile.close();
    }
    wideLayout = true;
    ushort winWidt, winHeight;

    switch(aSettings.resolution){
    case ArawnSettings::R800x600:
        winWidt = 800;
        winHeight = 600;
        wideLayout = false;
        break;
    case ArawnSettings::R1024x768:
        winWidt = 1024;
        winHeight = 768;
        wideLayout = false;
        break;
    case ArawnSettings::R1280x1024:
        winWidt = 1280;
        winHeight = 1024;
        wideLayout = false;
        break;
    case ArawnSettings::R1280x800:
        winWidt = 1280;
        winHeight = 800;
        break;
    case ArawnSettings::R1440x900:
        winWidt = 1440;
        winHeight = 900;
        break;
    case ArawnSettings::R1680x1050:
        winWidt = 1680;
        winHeight = 1050;
        break;
    case ArawnSettings::R1280x720:
        winWidt = 1280;
        winHeight = 720;
        break;
    case ArawnSettings::R1366x768:
        winWidt = 1366;
        winHeight = 768;
        break;
    }


    setGeometry(0, 0, winWidt, winHeight);

}
