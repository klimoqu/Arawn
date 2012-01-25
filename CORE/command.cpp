#include "command.hpp"

Command::Command()
{
    id=255;
    msgtype=0;
    msg=0;
}
Command::Command(uchar _id, uchar _msgtype, int _msg)
{
    id=_id;
    msgtype=_msgtype;
    msg=_msg;
}

uchar Command::GetPlayerId()const{return id;}
uchar Command::GetMessageType()const{return msgtype;}
int Command::GetMessage()const{return msg;}
QString Command::ToString()
{
	return QString("/command:") + QString::number(id) + QString(" ")+ QString::number(msgtype) + QString(" ") + QString::number(msg) + QString("\n");
}
