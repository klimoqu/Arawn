#include "arawnheader.h"

Command::Command(int _id, int _msgtype, int _msg)
{
    id=_id;
    msgtype=_msgtype;
    msg=_msg;
}

QDataStream & Command::operator <<(QDataStream &stream, Command &what)
{
    stream  << what.id;
    stream  << what.msgtype;
    stream  << what.msg;
    return( stream );
}

QDataStream & Command::operator >>(QDataStream &stream, Command &what)
{
    stream  >> what.id;
    stream  >> what.msgtype;
    stream  >> what.msg;
    return( stream );
}

int Command::GetMessage()
{
    return msg;
}

