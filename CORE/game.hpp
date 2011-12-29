#pragma once
#include "arawnheader.h"

class Game : public QObject
{
    Q_OBJECT
    Map* map;
    int time,playersnumber,timeout;
    bool server;

    void validate(Command c);
    void execute(Command c);


public:
    Game(int playersnumber,int timeout)
    {
        this->playersnumber=playersnumber;
        this->timeout=timeout;
    }
    void NewGame(int id);


signals:

    void ServerValidate(Command c);//ellenörzött cumó
    void KlientValidate(Command c);//elleőrizendő cumó

public slots:
    void ServerExecute(Command c){execute(c);}//ellenörzött parancs
    void KlientExecute(Command c){validate(c);}//ellenőrzés
};
