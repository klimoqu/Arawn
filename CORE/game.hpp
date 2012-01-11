#pragma once
#include "arawnsettings.hpp"
class ArawnSettings;
#include "CORE/map.hpp"
class Map;
#include "CORE/cup.hpp"
#include "NET/servernet.hpp"
#include "NET/client.hpp"

class Game : public QObject
{
    Q_OBJECT
    Map *map;
    Cup *cup;
    int gametime,playersnumber,bombtimeout;
    uchar playerid;
    ArawnSettings *settings;
    Servernet *serverconnection;
    Client *clientconnection;

    QMap<QTimer*,Command> tempcommands;

    void validate(Command c);//server
    void execute(Command c);//server
    void clientsync(Command c);//kliens


public:
    Game(QString address);
    Game(uchar playersnumber,int bombtimeout,ArawnSettings *settings);
    void SetCup(Cup *cup);
    void NewGame(int id);
    void SetGameTime(int time){this->gametime=time;}
    void MakeCommand(uchar c);

signals:

    void ServerValidate(Command c);//ellenörzött cumó
    void ClientValidate(Command c);//elleőrizendő cumó

    void Connected();//kliens
    void ConnectionFailed();//kliens+szerver

    void ServerIsRunning();//szerver
    void NewPlayer(QString newplayername);//szerver

    void BombPlanted(uchar x, uchar y,uchar id);
    void FieldBlasted(uchar x, uchar y, uchar id,uchar direction);
    void PlayerDied(uchar id,uchar murderid);
    void PlayerMoved(uchar id,uchar direction);
    void PlayerBlasted(uchar id);
    void FieldChanged(uchar x, uchar y, uchar newtype);
    void FieldExcinted(uchar x,uchar y);
    void BonusTurnVisible(uchar x, uchar y, uchar type);
    void BonusTurnInvisible(uchar x, uchar y, uchar type);
    void PlayerTurnVisible(uchar playerid);
    void PlayerTurnInvisible(uchar playerid);

private slots:
    void WaitingCommandExecute();

public slots:
    void ServerExecute(Command c){clientsync(c);}//ellenörzött parancs
    void ClientExecute(Command c){validate(c);}//ellenőrzés

    void InputCommandFromGui(uchar c){MakeCommand(c);}
    void InputCommandFromMap(Command c){ServerValidate(c);}
};
