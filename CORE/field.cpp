#include "arawnheader.h"

void Field::Boom(uchar x, uchar y, int size, uchar direction)
{
    if(x!=this->x || this->y!=y)return;
    burning=true;
    qt.stop();
    qt.setSingleShot(true);
    qt.start(1000);
    connect(&qt,SIGNAL(timeout()),this,SLOT(Extinction()));
    if(direction==0 && left!=0 && (left->IsPermeable() || left->IsBlastable())){emit Boomed(x-1,y,size-1,direction);}
    if(direction==1 && top!=0 && (top->IsPermeable() || top->IsBlastable())){emit Boomed(x,y-1,size-1,direction);}
    if(direction==2 && bottom!=0 && (bottom->IsPermeable() || bottom->IsBlastable())){emit Boomed(x,y+1,size-1,direction);}
    if(direction==3 && right!=0 && (right->IsPermeable() || right->IsBlastable())){emit Boomed(x+1,y,size-1,direction);}
}
void Field::Extinction()
{
    burning=false;
    emit Extincted(x,y);
}
