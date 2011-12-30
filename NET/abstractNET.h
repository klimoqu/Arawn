#ifndef ABSTRACTNET_H
#define ABSTRACTNET_H

//  str a változó neve, nem string

class abstractNet
{
public:
    bool isServer();                             //Server(true) vagy Client(false)
    void setIP(QString, quint8);

signals:
    void ServerNewMessage(Command str);         //új bejövõ üzenet klienstõl signal
    void ClientNewMessage(Command str);         //új bejövõ üzenet szervertõl signal

    void ServerSendMessage(Command str);        //új üzenet kiküldése mindenkinek signal
    void ClientSendMessage(Command str);        //új üzenet szervernek signal

    void finish();                              //kilépés signal

public slots:


};

#endif // ABSTRACTNET_H
