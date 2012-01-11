#pragma once

#include <fstream>
#include <string>
#include "arawnsettings.hpp"
class ArawnSettings;
#include "CORE/field.hpp"
#include "CORE/bomb.hpp"
#include "CORE/player.hpp"
#include "CORE/command.hpp"
#include "CORE/bonus.hpp"

class Map : public QObject
{
    Q_OBJECT
private:
    std::string name;
    int id;
    std::ifstream input;
    Field* Fields[20][13];
    Player* players[4];
    uchar playersnumber;
    QList<Bomb*> bombs;
    ArawnSettings *settings;
    void bonusupload();


public:
    void Upload(int id);
    Map(uchar playersnumber,ArawnSettings *settings);
    uchar GetPlayersNumber(){return playersnumber;}
    Player* GetPlayer(uchar id){return id>=playersnumber ? 0:players[id];}
    Field* GetField(uchar x, uchar y){return Fields[x][y];}
    Bomb* GetBomb(int i){return bombs[i];}
    void AddBomb(Bomb* b){bombs.push_back(b);}
    void SetPlayersStartPoints();

signals:

    void ServerCommand(Command c);
    void FieldBlasted(uchar x, uchar y, uchar id,uchar direction);

public slots:
    void DeleteThis(Bomb *b)
    {
        bombs.removeAll(b);
        delete b;
    }
    void FieldBurning(uchar x, uchar y, uchar id,uchar direction)
    {
        Command ret=Command(id,3,256*256*direction+256*x+y);
        emit ServerCommand(ret);
    }
    void FieldExcinguish(uchar x, uchar y)
    {
        Command ret=Command(255,4,256*x+y);
        emit ServerCommand(ret);
    }
    void FieldChange(uchar x, uchar y,uchar newtype)
    {
        Command ret=Command(255,6,256*256*newtype+256*x+y);
        emit ServerCommand(ret);
    }
    void PlayerDie(uchar id,uchar murderid)
    {
        Command ret=Command(id,5,murderid);
        emit ServerCommand(ret);
    }
    void PlayerBlast(uchar id)
    {
        Command ret=Command(id,5,256);
        emit ServerCommand(ret);
    }
    void ChangeBonus(uchar x, uchar y, uchar type,uchar visibleorstate)
    {
        Command ret=Command(0,7,(visibleorstate*256*256*256)+(256*256*type)+(256*x)+y);
        emit ServerCommand(ret);
    }
    void PlayerInvisibility(uchar playerid,bool visible)
    {
        Command ret=Command(playerid,7,(((visible?3:4))*256*256*256));
        emit ServerCommand(ret);
    }
};
