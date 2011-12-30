#include "command.hpp"

Command::Command(uchar _id, uchar _msgtype, int _msg)
{
    id=_id;
    msgtype=_msgtype;
    msg=_msg;
}

uchar Command::GetPlayerId(){return id;}
uchar Command::GetMessageType(){return msgtype;}
int Command::GetMessage(){return msg;}

QString Command::toString()
{
    return (QString::number(this->id) + " " + QString::number(this->msgtype) + " " + QString::number(this->msg));
}
