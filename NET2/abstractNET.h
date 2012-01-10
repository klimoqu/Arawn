#ifndef ABSTRACTNET_H
#define ABSTRACTNET_H

//  str a változó neve, nem string
//  port : 28300

class abstractNet
{
public:
    bool isServer();                             //Server(true) vagy Client(false)
    void setIP(QString, quint8);

signals:
    void ServerNewMessage(Command *str);         //új bejövõ üzenet klienstõl signal
    void ClientNewMessage(Command *str);         //új bejövõ üzenet szervertõl signal
    void NewClientConnected();                   //szerver: Új kliens kapcsolódott
    void ConnectedToServer();                    //kliens: szerverhez kapcsolódás sikeres

    void finish();                               //kilépés signal

    void debugs(QString);

public slots:
    void ServerSendMessage(Command *str);        //új üzenet kiküldése mindenkinek signal
    void ClientSendMessage(Command *str);        //új üzenet szervernek signal
};

#endif // ABSTRACTNET_H
