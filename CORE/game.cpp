#include "game.hpp"

game::game(QTcpSocket socket)
{
    {
        self.server=socket;
    }
}
game::game(QTcpSocket socket0,QTcpSocket socket1,QTcpSocket socket2,QTcpSocket socket3)
{
    clients=new QTcpSocket[4];
    clients[0]=socket0;
    clients[1]=socket1;
    clients[2]=socket2;
    clients[3]=socket3;
}
void game::newGame(int id){}
void game::validate(Command c){}
void game::execute(Command c){}
