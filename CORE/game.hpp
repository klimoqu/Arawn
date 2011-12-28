#pragma once

class game
{
    Map* map;
    int time;
    QTcpSocket server;
    QTcpSocket clients[];
public:
    game(QTcpSocket socket)
    {
        self.server=socket;
    }
    game(QTcpSocket socket1,QTcpSocket socket2,QTcpSocket socket3,QTcpSocket socket4);

    void newGame(int id);
    void validate(Command c);
    void execute(Command c);
};
