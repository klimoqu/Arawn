#pragma once
#include "arawnheader.h"
#include "CORE/map.hpp"
#include "CORE/command.hpp"

class game : public QObject
{
    Q_OBJECT
    Map* map;
    int time;
    bool server;
public:
    game();

    void newGame(int id);
    void validate(Command c);
    void execute(Command c);

signals:

    void ServerValidate(Command c);
    void KlientValidate(Command c);

public slots:
    void ServerExecute(Command c){}
    void KlientExecute(Command c){}
};
