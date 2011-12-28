#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command
{
    int id,msgtype,msg;
public:
    Command(int _id, int _msgtype, int _msg)
    {
        id=_id;
        msgtype=_msgtype;
        msg=_msg;
    }
    Command(){}
    int GetPlayerId(){return id;}
    int GetMessageType(){return msgtype;}
    int GetMessage(){return msg;}

    friend QDataStream & operator<<(QDataStream & stream, Command & what);
    friend QDataStream & operator>>(QDataStream & stream, Command & what);
};

QDataStream & operator >> ( QDataStream & stream, Command & what )
{
    stream  >> what.id;
    stream  >> what.msgtype;
    stream  >> what.msg;
    return( stream );
}

QDataStream & operator << ( QDataStream & stream, Command & what )
{
    stream  << what.id;
    stream  << what.msgtype;
    stream  << what.msg;
    return( stream );
}


#endif // COMMAND_HPP
