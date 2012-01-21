#include "field.hpp"
#include <QtCore>
/*
  0 - Fal
  1 - Doboz
  2 - Fű
  3 - Nehézdoboz
  4 - Űr
  5 - Lyuk
*/
Field::Field(uchar x,uchar y,uchar type)
{
    this->x=x;
    this->y=y;
    this->type=type;
    this->id=255;
    this->burning=false;
    this->top=0;
    this->bottom=0;
    this->left=0;
    this->right=0;
    this->bonus=0;
}
void Field::Boom(uchar x, uchar y, uchar size, uchar id,uchar direction)
{
    if(x!=this->x || this->y!=y)return;
    StartBurn(size,id,255);
}
void Field::Extinction()
{
    burning=false;
    this->id=255;
    emit Extincted(x,y);
}
void Field::StartBurn(uchar size, uchar id,uchar direction)
{
	switch(type)
	{
	case 2:
		burning=true;
		if(bonus)
		{
			bonus->Destroy();
			bonus=0;
		}
		this->id=id;
		break;
	case 3:
		this->type=1;
		emit FieldChanged(this->x,this->y,this->type);
		break;
	case 1:
		this->type=2;
		emit FieldChanged(this->x,this->y,this->type);
		if(bonus)bonus->TurnVisible();
		break;
	}
	QTimer::singleShot(500,this,SLOT(Extinction()));

    emit Boomed(x,y,size,id,size==0 ? direction+16 :direction);

    if( size==0 || !burning)return;

    if((direction==0 || direction==255) && left!=0 && (left->IsPermeable() || left->IsBlastable())){left->StartBurn(size-1,id,0);}
    if((direction==1 || direction==255) && top!=0 && (top->IsPermeable() || top->IsBlastable())){top->StartBurn(size-1,id,1);}
    if((direction==2 || direction==255) && bottom!=0 && (bottom->IsPermeable() || bottom->IsBlastable())){bottom->StartBurn(size-1,id,2);}
    if((direction==3 || direction==255) && right!=0 && (right->IsPermeable() || right->IsBlastable())){right->StartBurn(size-1,id,3);}

}
void Field::SetBonus(Bonus *bonus)
{
    if(this->type==0||this->type>3){delete bonus;return;}
    this->bonus=bonus;
    connect(bonus,SIGNAL(TurnedVisible()),this,SLOT(BonusTurnToVisible()));
    connect(bonus,SIGNAL(PickUpOrDestroyed()),this,SLOT(BonusPickUpOrDestroyed()));
	if(this->type==2){bonus->TurnVisible();}
}
void Field::Visit(Player* player)
{
    if(bonus)bonus->Pickup(player);
    bonus=0;
}
