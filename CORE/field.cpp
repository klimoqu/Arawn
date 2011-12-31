#include "CORE/field.hpp"

void Field::Boom(uchar x, uchar y, uchar size, uchar id,uchar direction)
{
    if(x!=this->x || this->y!=y)return;
    StartBurn(size,id,direction);
}
void Field::Extinction()
{
    burning=false;
    emit Extincted(x,y);
}
void Field::StartBurn(uchar size, uchar id,uchar direction)
{
    burning=true;
    qt.stop();
    qt.setSingleShot(true);
    qt.start(1000);
    connect(&qt,SIGNAL(timeout()),this,SLOT(Extinction()));

    emit Boomed(x,y,id,size==0 ? direction+16 :direction);

    if(size==0)return;

    if((direction==0 || direction==255) && left!=0 && (left->IsPermeable() || left->IsBlastable())){left->StartBurn(size-1,id,0);}
    if((direction==1 || direction==255) && top!=0 && (top->IsPermeable() || top->IsBlastable())){top->StartBurn(size-1,id,1);}
    if((direction==2 || direction==255) && bottom!=0 && (bottom->IsPermeable() || bottom->IsBlastable())){bottom->StartBurn(size-1,id,2);}
    if((direction==3 || direction==255) && right!=0 && (right->IsPermeable() || right->IsBlastable())){right->StartBurn(size-1,id,3);}

}
