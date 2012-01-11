#include "CORE/map.hpp"
#include <sstream>

void Map::Upload(int id)
{
    this->id=id;
    std::stringstream ss;
    ss<<id;
    std::string stringid;
    ss>>stringid;
    std::string filename="maps/"+stringid+".map";
    std::cout<<filename;
    std::cout.flush();
    input.open(filename.c_str());
    getline(input,name);
    for(unsigned int i=0;i<20;i++)
    {
        for(unsigned int j=0;j<13;j++)
        {
            int tempFieldid;
            input>>tempFieldid;
            Fields[i][j]=new Field(i,j,tempFieldid);
            connect(Fields[i][j],SIGNAL(Boomed(uchar,uchar,uchar,uchar)),this,SLOT(FieldBurning(uchar,uchar,uchar,uchar)));
            connect(Fields[i][j],SIGNAL(Extincted(uchar,uchar)),this,SLOT(FieldExcinguish(uchar,uchar)));
            connect(Fields[i][j],SIGNAL(FieldChanged(uchar,uchar,uchar)),this,SLOT(FieldChange(uchar,uchar,uchar)));
            connect(this,SIGNAL(FieldBlasted(uchar,uchar,uchar,uchar)),Fields[i][j],SLOT(FieldBurning(uchar,uchar,uchar,uchar)));
            for(uchar k=0;k<playersnumber;k++)
            {
                connect(Fields[i][j],SIGNAL(FieldBlasted(uchar,uchar,uchar,uchar)),players[k],SLOT(DieAndBlast(uchar,uchar,uchar,uchar)));
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
}
Map::Map(uchar playersnumber,ArawnSettings *settings)
{
    this->settings=settings;
    this->playersnumber=playersnumber;
    for(uchar i=0;i<playersnumber;i++)
    {
        players[i]=new Player(i);
        connect(players[i],SIGNAL(Blasted(uchar)),this,SLOT(PlayerBlast(uchar)));
        connect(players[i],SIGNAL(Died(uchar,uchar)),this,SLOT(PlayerDie(uchar,uchar)));
    }
}
