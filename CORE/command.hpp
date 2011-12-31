#pragma once

#include <QString>

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
