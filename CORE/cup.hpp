#pragma once
#include <QtCore>
#include "CORE/player.hpp"
#include "arawnsettings.hpp"
class ArawnSettings;

class Cup : public QObject
{
    Q_OBJECT
    ArawnSettings *settings;
    QString nevek[4];
    int pontok[4];
    uchar playersnumber;
public:
    Cup(ArawnSettings *settings);

    void AddPlayer(QString str)
    {
        if(playersnumber<4)
        {
            nevek[playersnumber]=str;
            playersnumber++;
        }
    }
    QString GetPlayerName(uchar num)
    {
        return nevek[num];
    }
    QStringList GetPlayersName()
    {
        QStringList qsl;
        for(uchar i=0;i<playersnumber;i++)qsl<<nevek[i];
        return qsl;
    }
signals:
    void PlayerWonTheCup(uchar playerid, QString playername);
public slots:
    void playerdie(uchar victim, uchar murder)
    {
        if(victim!=murder)pontok[murder]++;
        else pontok[victim]--;
        if(pontok[murder]==settings->pointsToWin.toInt())emit PlayerWonTheCup(murder,nevek[murder]);
    }
    void playersurvive(uchar surviver)
    {
        pontok[surviver]++;
        if(pontok[surviver]==settings->pointsToWin.toInt())emit PlayerWonTheCup(surviver,nevek[surviver]);
    }
};
