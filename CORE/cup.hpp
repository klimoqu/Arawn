#pragma once
#include <QtCore>
#include "player.hpp"
#include "../arawnsettings.hpp"

class Cup : public QObject
{
    Q_OBJECT
    ArawnSettings *settings;
    QString nevek[4];
    int pontok[4];
    uchar playersnumber;
	bool finish;
public:
    Cup(ArawnSettings *settings);
	Cup();
	bool Finished()const{return finish;}
    void AddPlayer(QString str)
    {
        if(playersnumber<4)
        {
            nevek[playersnumber]=str;
            playersnumber++;
        }
    }
    QString GetPlayerName(uchar num)const
    {
        return num<playersnumber?nevek[num]:QString("");
    }
    QStringList GetPlayersName()
    {
        QStringList qsl;
        for(uchar i=0;i<playersnumber;i++)qsl<<nevek[i];
        return qsl;
    }
    int GetPointOf(uchar id)const {return pontok[id];}
signals:
    void PlayerWonTheCup(uchar playerid, QString playername);
    void PlayerPointChanged(uchar playerid,int point);
public slots:
	void ChangePlayerPoint(uchar playerid,int point){pontok[playerid]=point;}
    void PlayerDie(uchar victim, uchar murder);
    void PlayerSurvive(uchar surviver);
};
