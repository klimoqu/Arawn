#pragma once
#include "CORE/map.hpp"

//class Map;
class Game : public QObject
{
    Q_OBJECT
    Map *map;
    int gametime,playersnumber,bombtimeout;
    uchar playerid;
    bool server;

    void validate(Command c);//server
    void execute(Command c);//server
    void clientsync(Command c);//kliens


public:
    Game(int playersnumber,bool server,uchar playerid);
    void NewGame(int id);
    void SetGameTime(int time){this->gametime=time;}
    void MakeCommand(uchar c);

signals:

    void ServerValidate(Command c);//ellenörzött cumó
    void KlientValidate(Command c);//elleőrizendő cumó

public slots:
    void ServerExecute(Command c){clientsync(c);}//ellenörzött parancs
    void KlientExecute(Command c){validate(c);}//ellenőrzés

    void InputCommandFromGui(uchar c){MakeCommand(c);}
    void InputCommandFromMap(Command c){ServerValidate(c);}
};
