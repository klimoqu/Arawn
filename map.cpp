#include "map.hpp"

Map::Map(int id)
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
