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
Map::Map(int playersnumber)
{
    this->playersnumber=playersnumber;
    for(uchar i=0;i<playersnumber;i++)
    {
        players[i]=new Player(i);
    }
}
