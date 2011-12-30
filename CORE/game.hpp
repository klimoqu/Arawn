#pragma once
#include "arawnheader.h"

class Game : public QObject
{
    Q_OBJECT
    Map* map;
    int gametime,playersnumber,bombtimeout;
    bool server;

    void validate(Command c);
    void execute(Command c);


public:
    Game(int playersnumber)
    {
        this->playersnumber=playersnumber;
        this->bombtimeout=2500;
    }
    void NewGame(int id);
    void SetGameTime(int time){this->gametime=time;}


signals:

    void ServerValidate(Command c);//ellenörzött cumó
    void KlientValidate(Command c);//elleőrizendő cumó

public slots:
    void ServerExecute(Command c){execute(c);}//ellenörzött parancs
    void KlientExecute(Command c){validate(c);}//ellenőrzés
};
