#pragma once
#include "map.hpp"
#include "cup.hpp"
#include "../NET/servernet.hpp"
#include "../NET/client.hpp"
class Game : public QObject
{
    Q_OBJECT
    bool survive,activegame;
    Map *map;
    Cup *cup;
    int gametime,playersnumber,bombtimeout,act;
    uchar playerid;
    ArawnSettings *settings;
    Servernet *serverconnection;
    Client *clientconnection;
    QTimer *gametimer,*destroymap;
    QMap<QTimer*,Command> tempcommands;
    uchar fields[20][13];

    void validate(Command c);//server
    void execute(Command c);//server
    void clientsync(Command c);//kliens
    void sendmap();

public:
    Game(QString address);
    Game(uchar playersnumber,int bombtimeout,ArawnSettings *settings,bool survive);
    void SetCup(Cup *cup);
    void NewGame(int id);
    void SetGameTime(int time){this->gametime=time;}
    void MakeCommand(uchar c);
    QStringList GetPlayers();
	uchar GetPlaysersNumber();
    uchar GetFields(uchar x, uchar y){return fields[x][y];}
    bool IsSurvive() const {return survive;}
	bool IsServer()const{return map;}
    Cup* GetCup() const {return cup;}
    void ConnectToServer(QString);
	void GameIsEnd();

signals:

    void ServerValidate(Command c);//ellenörzött cumó
    void ClientValidate(Command c);//elleőrizendő cumó

    void Connected();//kliens
    void ConnectionFailed();//kliens+szerver
    void RefreshPlayers();
	void Disconnected();

    void ServerIsRunning();//szerver
    void NewPlayer();//szerver

    void SetPlayerStartPosition(uchar id, uchar x, uchar y);
    void GameStarted(int roundtime);

	void DeleteBomb(uchar x, uchar y);
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

    void PlayerSurvived(uchar id);
	void PlayerWonTheRound(QString winnername);
    void PlayerWonTheCup(QString winnername);
    void PlayerPointChanged(uchar id, int point);
    void GameOver();
    void FieldDestroyedByMap(uchar x,uchar y);

private slots:
    void WaitingCommandExecute();
    void StartGame();
    void TimeIsOver();
    void DestroyField();
	void StopTheGame(){GameIsEnd();}

public slots:
    void ServerExecute(Command c){clientsync(c);}//ellenörzött parancs
    void ClientExecute(Command c){validate(c);}//ellenőrzés

    void InputCommandFromGui(uchar c){MakeCommand(c);}
    void InputCommandFromMap(Command c){ServerValidate(c);}

    void AllReady();
    void PlayerWinTheCup(uchar playerid,QString name);
    void ChangePlayerPoint(uchar id, int point){emit ServerValidate(Command(id,0,point));}

};
