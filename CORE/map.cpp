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
    input>>size_x;
    input>>size_y;
    for(unsigned int i=0;i<size_x;i++)
    {
        std::vector<Field*> tempcolumn;
        for(unsigned int j=0;j<size_y;j++)
        {
            int tempFieldid;
            input>>tempFieldid;
            tempcolumn.push_back(new Field(i,j,tempFieldid));
        }
        Fields.push_back(tempcolumn);
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
    o<<size_x<<" "<<size_y<<std::endl;
    for(int i=0;i<size_x;i++)
    {
        for(int j=0;j<size_y;j++)
        {
            Fields[i][j]->Save(o);
        }
    }
    o.flush();
}
void Map::Load(std::istream &i)
{

}
