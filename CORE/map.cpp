#include "map.hpp"
#include <sstream>

Map::Map(uchar playersnumber,ArawnSettings *settings)
{
    Fields[0][0] = 0;
    this->settings=settings;
    this->playersnumber=playersnumber;
    for(uchar i=0;i<playersnumber;i++)
    {
        players[i]=new Player(i,(uchar)settings->startBombs.toInt(),(uchar)settings->startFire.toInt(),(uchar)settings->maxBombs.toInt(),(uchar)settings->maxFire.toInt());
        connect(players[i],SIGNAL(Blasted(uchar)),this,SLOT(PlayerBlast(uchar)));
        connect(players[i],SIGNAL(Died(uchar,uchar)),this,SLOT(PlayerDie(uchar,uchar)));
        connect(this,SIGNAL(FieldDestroyed(uchar,uchar)),players[i],SLOT(Die(uchar,uchar)));
    }
}
void Map::Upload(int id)
{
    if(Fields[0][0])
        for(uchar i=0; i<20; i++)
            for(uchar j = 0; j < 13; j++)
                    delete Fields[i][j];


    bombs.clear();

    this->id=id;
    std::stringstream ss;
    ss<<id;
    std::string stringid;
    ss>>stringid;
    std::string filename="maps/"+stringid+".map";
    input.open(filename.c_str());
    for(unsigned int i=0;i<20;i++)
    {
        for(unsigned int j=0;j<13;j++)
        {
            int tempFieldid;
            input>>tempFieldid;
            Fields[i][j]=new Field(i,j,(uchar)tempFieldid);
            connect(Fields[i][j],SIGNAL(Boomed(uchar,uchar,uchar,uchar,uchar)),this,SLOT(FieldBurning(uchar,uchar,uchar,uchar,uchar)));
            connect(Fields[i][j],SIGNAL(Extincted(uchar,uchar)),this,SLOT(FieldExcinguish(uchar,uchar)));
            connect(Fields[i][j],SIGNAL(FieldChanged(uchar,uchar,uchar)),this,SLOT(FieldChange(uchar,uchar,uchar)));
            connect(this,SIGNAL(FieldBlasted(uchar,uchar,uchar,uchar,uchar)),Fields[i][j],SLOT(Boom(uchar,uchar,uchar,uchar,uchar)));
            for(uchar k=0;k<playersnumber;k++)
            {
                connect(Fields[i][j],SIGNAL(Boomed(uchar,uchar,uchar,uchar,uchar)),players[k],SLOT(DieAndBlast(uchar,uchar,uchar,uchar,uchar)));
            }
            if(i>0)
            {
                Fields[i][j]->SetLeftNeighbours(Fields[i-1][j]);
                Fields[i-1][j]->SetRightNeighbours(Fields[i][j]);
            }
            if(j>0)
            {
                Fields[i][j]->SetTopNeighbours(Fields[i][j-1]);
                Fields[i][j-1]->SetBottomNeighbours(Fields[i][j]);
            }
        }
    }
    input.close();
    bonusupload();
}
void Map::bonusupload()
{
    for(unsigned int i=0;i<20;i++)
    {
        for(unsigned int j=0;j<13;j++)
        {
            switch(((int)Fields[i][j])%60)
            {
            case 1:
            case 2:
            case 3:
            case 4:Fields[i][j]->SetBonus(new Bonus(1));break;//bomba erő +
            case 5:
            case 6:Fields[i][j]->SetBonus(new Bonus(2));break;//bomba erő -
            case 7:
            case 8:
            case 9:
            case 10:Fields[i][j]->SetBonus(new Bonus(3));break;//bomba darab +
            case 11:
            case 12:Fields[i][j]->SetBonus(new Bonus(4));break;//bomba darab -
            case 13:Fields[i][j]->SetBonus(new Bonus(5));break;//sebesség +
            case 14:Fields[i][j]->SetBonus(new Bonus(6));break;//sebesség -
            case 15:if(settings->enableInvisibility.toBool())Fields[i][j]->SetBonus(new Bonus(7));break;//láthatatlanság
            case 16:
            case 17:if(settings->enableOppositeControls.toBool())Fields[i][j]->SetBonus(new Bonus(8));break;//ellenkontrol
            case 18:
            case 19:if(settings->enableFailingBombs.toBool())Fields[i][j]->SetBonus(new Bonus(9));break;//besülés
            default:break;
            }
        }
    }
}
void Map::SetPlayersStartPoints()
{
    switch(playersnumber)
    {
    case 4:players[3]->SetStartPosition(19,12);emit ServerCommand(Command(3,254,19*256+12));
    case 3:players[2]->SetStartPosition(0,12);emit ServerCommand(Command(2,254,12));
    case 2:players[1]->SetStartPosition(19,0);emit ServerCommand(Command(1,254,19*256));
    default:players[0]->SetStartPosition(0,0);emit ServerCommand(Command(0,254,0));
        break;
    }
}
