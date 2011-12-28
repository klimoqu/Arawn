#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command
{
    int id,msgtype,msg;
public:
    Command(nt id, int msgtype,int msg)
    {
        self.id=id;
        self.msgtype=msgtype;
        self.msg=msg;
    }
    int GetPlayerId(){return id;}
    int GetMessageType(){return msgtype;}
    int GetMessage(){return msg;}
};

#endif // COMMAND_HPP
