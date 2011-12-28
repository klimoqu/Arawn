#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command
{
    int id,msgtype,msg;
public:
    Command(int _id, int _msgtype,int _msg)
    {
        id=_id;
        msgtype=_msgtype;
        msg=_msg;
    }
    int GetPlayerId(){return id;}
    int GetMessageType(){return msgtype;}
    int GetMessage(){return msg;}
};

#endif // COMMAND_HPP
