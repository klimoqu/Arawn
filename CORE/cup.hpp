#pragma once
#include <QString>
#include "CORE/player.hpp"
class Cup : public QObject
{
    Q_OBJECT
    QString nevek[4];
    int pontok[4];
    uchar playersnumber;
public:
    Cup();
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
signals:
public slots:
    void changepoint(uchar id,int change)
    {
        if(id<playersnumber)pontok[id]+=change;
    }
};
