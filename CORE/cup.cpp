#include "cup.hpp"

Cup::Cup(ArawnSettings *settings)
{
    playersnumber=0;
    pontok[0]=0;
    pontok[1]=0;
    pontok[2]=0;
    pontok[3]=0;
    this->settings=settings;
	finish=false;
}
Cup::Cup()
{
    playersnumber=0;
    pontok[0]=0;
    pontok[1]=0;
    pontok[2]=0;
    pontok[3]=0;
	settings=0;
}
void Cup::PlayerDie(uchar victim, uchar murder)
{
    if(murder==255)return;
    if(victim!=murder)
        pontok[murder]++;
    else
        pontok[victim]--;
    emit PlayerPointChanged(murder,pontok[murder]);
    if(settings && pontok[murder]==settings->pointsToWin.toInt())
	{
		finish=true;
		emit PlayerWonTheCup(murder,nevek[murder]);
	}
}
void Cup::PlayerSurvive(uchar surviver)
{
    pontok[surviver]++;
    emit PlayerPointChanged(surviver,pontok[surviver]);
    if(settings && pontok[surviver]==settings->pointsToWin.toInt())
	{
		finish=true;
		emit PlayerWonTheCup(surviver,nevek[surviver]);
	}
}
