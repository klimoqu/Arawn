#pragma once

#include <fstream>
#include <string>
#include "../arawnsettings.hpp"
#include "field.hpp"
#include "bomb.hpp"
#include "player.hpp"
#include "command.hpp"
#include "bonus.hpp"

class Map : public QObject
{
    Q_OBJECT
private:
    std::string name;
    int id;
    std::ifstream input;
    Field* Fields[20][13];
    Player* players[4];
    uchar playersnumber,deadplayersnumber;
    QList<Bomb*> bombs;
    ArawnSettings *settings;
	bool activegame;
    
public:
    void Upload(int id);
	void bonusupload();
    Map(uchar playersnumber,ArawnSettings *settings);
    uchar GetPlayersNumber()const{return playersnumber;}
    Player* GetPlayer(uchar id)const{return id>=playersnumber ? 0:players[id];}
    Field* GetField(uchar x, uchar y)const{return Fields[x][y];}
    Bomb* GetBomb(int i)const {return bombs[i];}
    void AddBomb(Bomb* b)
    {
        bombs.push_back(b);
        connect(b,SIGNAL(Boomed(uchar,uchar,uchar,uchar,uchar)),this,SIGNAL(FieldBlasted(uchar,uchar,uchar,uchar,uchar)));
		connect(b,SIGNAL(Failed(uchar,uchar)),this,SLOT(BombFail()));
    }
    void SetPlayersStartPoints();
	void ClearMap();

signals:

    void ServerCommand(Command c);
    void FieldBlasted(uchar x, uchar y, uchar size,uchar id,uchar direction);
    void FieldDestroyed(uchar x, uchar y);
public slots:
	void BombFail(uchar x, uchar y)
	{
		Command ret=Command(255,249,256*x+y);
        if(activegame)emit ServerCommand(ret);
	}
    void DeleteThis(Bomb *b)
    {
        bombs.removeAll(b);
        delete b;
    }
    void FieldBurning(uchar x, uchar y,uchar size, uchar id,uchar direction)
    {
        Command ret=Command(id,3,256*256*direction+256*x+y);
        if(activegame)emit ServerCommand(ret);
    }
    void FieldExcinguish(uchar x, uchar y)
    {
        Command ret=Command(255,4,256*x+y);
        if(activegame)emit ServerCommand(ret);
    }
    void FieldChange(uchar x, uchar y,uchar newtype)
    {
        Command ret=Command(255,6,256*256*newtype+256*x+y);
        if(activegame)emit ServerCommand(ret);
    }
    void PlayerDie(uchar id,uchar murderid)
    {
		deadplayersnumber++;
        Command ret=Command(id,5,murderid);
        emit ServerCommand(ret);
		if(deadplayersnumber==playersnumber-1)
		{
			for(uchar i=0;i<playersnumber;i++)if(players[i]->IsAlive())emit ServerCommand(Command(i,253,1));
		}
    }
    void PlayerBlast(uchar id)
    {
        Command ret=Command(id,5,256);
        if(activegame)emit ServerCommand(ret);
    }
    void ChangeBonus(uchar x, uchar y, uchar type,uchar visibleorstate)
    {
        Command ret=Command(0,7,(visibleorstate*256*256*256)+(256*256*type)+(256*x)+y);
        if(activegame)emit ServerCommand(ret);
    }
    void PlayerInvisibility(uchar playerid,bool visible)
    {
        Command ret=Command(playerid,7,(((visible?3:4))*256*256*256));
        if(activegame)emit ServerCommand(ret);
    }
};
