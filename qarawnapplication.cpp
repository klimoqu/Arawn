#include <QFile>
#include <QDir>
#include <QDataStream>

#include "qarawnapplication.hpp"

QArawnApplication::QArawnApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
#ifdef Q_OS_WIN
    if(!QDir::exists(QDir::homePath() + "/AppData/Arawn")){
        QDir::mkdir(QDir::homePath() + "/AppData/Arawn");
    }
    path = QString(QDir::homePath() + "/AppData/Arawn/");
#else
    if(!QDir::exists(QDir::homePath() + "/.config/Arawn")){
        QDir::mkdir(QDir::homePath() + "/.config/Arawn");
    }
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
