#pragma once
#include <QtCore>
/*
  0 pontok átvitele
  1 mozgások
  2 bombalerakás
  3 robbanások
  4 kioltások
  5 halál, test robbanása
  6 mezőváltozás
  7 bonuszok
  250 mezők szinkronizálása
  251 játék kezdete
  252 játék vége
  253 játékos nyert
  254 starthelyek beállítása
  255 id beállítás
*/
class Command
{
    uchar id,msgtype;
    int msg;
public:
    Command();
    Command(uchar _id, uchar _msgtype, int _msg);
    uchar GetPlayerId();
    uchar GetMessageType();
    int GetMessage();
};
