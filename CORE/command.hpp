#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "QObject"

class Command
{
    uchar id,msgtype;
    int msg;
public:
    Command(uchar _id, uchar _msgtype, int _msg);

    uchar GetPlayerId();
    uchar GetMessageType();
    int GetMessage();

    QString toString();
};

#endif // COMMAND_HPP
