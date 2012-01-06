#pragma once
#include "CORE/map.hpp"
#include "CORE/cup.hpp"
class Game : public QObject
{
    Q_OBJECT
    Map *map;
    Cup *cup;
    int gametime,playersnumber,bombtimeout;
    uchar playerid;
    bool server;

    void validate(Command c);//server
    void execute(Command c);//server
    void clientsync(Command c);//kliens


public:
    Game(uchar playerid);
    Game(uchar playersnumber,int bombtimeout);
    void SetCup(Cup *cup);
    void NewGame(int id);
    void SetGameTime(int time){this->gametime=time;}
    void MakeCommand(uchar c);

signals:

    void ServerValidate(Command c);//ellenörzött cumó
    void ClientValidate(Command c);//elleőrizendő cumó


    void BombPlanted(uchar x, uchar y,uchar id);
    void FieldBlasted(uchar x, uchar y, uchar id,uchar direction);
    void PlayerDied(uchar id,uchar murderid);
    void PlayerMoved(uchar id,uchar direction);
    void PlayerBlasted(uchar id);
    void FieldChanged(uchar x, uchar y, uchar newtype);
    void FieldExcinted(uchar x,uchar y);


public slots:
    void ServerExecute(Command c){clientsync(c);}//ellenörzött parancs
    void ClientExecute(Command c){validate(c);}//ellenőrzés

    void InputCommandFromGui(uchar c){MakeCommand(c);}
    void InputCommandFromMap(Command c){ServerValidate(c);}
};
