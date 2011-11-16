#include <QFile>
#include <QDir>
#include <QDataStream>

#include "qarawnapplication.hpp"

QDataStream &operator >>(QDataStream &stream, QArawnApplication::ArawnSettings &settings)
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


QDataStream &operator <<(QDataStream &stream, const QArawnApplication::ArawnSettings &settings)
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


QArawnApplication::QArawnApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
#ifdef Q_OS_WIN
    QDir dir(QDir::homePath() + "/AppData/Arawn");
    if(!dir.exists())
        QDir::home().mkdir("/AppData/Arawn");
    path = QString(QDir::homePath() + "/AppData/Arawn/");
#else
    QDir dir(QDir::homePath() + "/.config/Arawn");
    if(!dir.exists())
        QDir::home().mkdir("/.config/Arawn");
    path = QString(QDir::homePath() + "/.config/Arawn/");
#endif
    if(QFile::exists(path+"gamesettings")){
        QFile sFile(path+"gamesettings");
        sFile.open(QFile::ReadOnly);
        QDataStream sReader(&sFile);
        sReader >> aSettings;
        sFile.close();
    }

}
