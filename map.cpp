#include "map.h"
#include <string>
map::map(int id)
{
    this->id=id;
    std::string filename="maps/";
    filename+=id;
    filename+=".map";
    input.open(filename.c_str());
    input>>size_x;
    input>>size_y;
    for(unsigned int i=0;i<size_x;i++)
    {
        std::vector<field*> tempcolumn;
        for(unsigned int j=0;j<size_y;j++)
        {
            int tempfieldid;
            input>>tempfieldid;
            tempcolumn.push_back(new field(tempfieldid));
        }
        fields.push_back(tempcolumn);
    }
    input.close();
}
void map::Save()
{

}
void map::Load()
{

}
