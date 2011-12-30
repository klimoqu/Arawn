#include "arawnheader.h"

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
Map::Map(int id,Player* player_0,Player* player_1)
{
    Upload(id);
    playersnumber=2;
    players[0]=player_0;
    players[1]=player_1;
}
Map::Map(int id,Player* player_0,Player* player_1,Player* player_2)
{
    Upload(id);
    playersnumber=3;
    players[0]=player_0;
    players[1]=player_1;
    players[2]=player_2;
}
Map::Map(int id,Player* player_0,Player* player_1,Player* player_2,Player* player_3)
{
    Upload(id);
    playersnumber=4;
    players[0]=player_0;
    players[1]=player_1;
    players[2]=player_2;
    players[3]=player_3;
}

void Map::Save(std::ostream &o)
{
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<13;j++)
        {
            Fields[i][j]->Save(o);
        }
    }
    o.flush();
}
void Map::Load(std::istream &i)
{

}
