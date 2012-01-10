#ifndef ABSTRACTNET_H
#define ABSTRACTNET_H

//  str a v�ltoz� neve, nem string
//  port : 28300

class abstractNet
{
public:
    bool isServer();                             //Server(true) vagy Client(false)
    void setIP(QString, quint8);

signals:
    void ServerNewMessage(Command *str);         //�j bej�v� �zenet klienst�l signal
    void ClientNewMessage(Command *str);         //�j bej�v� �zenet szervert�l signal
    void NewClientConnected();                   //szerver: �j kliens kapcsol�dott
    void ConnectedToServer();                    //kliens: szerverhez kapcsol�d�s sikeres

    void finish();                               //kil�p�s signal

    void debugs(QString);

public slots:
    void ServerSendMessage(Command *str);        //�j �zenet kik�ld�se mindenkinek signal
    void ClientSendMessage(Command *str);        //�j �zenet szervernek signal
};

#endif // ABSTRACTNET_H
