#pragma once
#include <QObject>
#include "CORE/command.hpp"

//  str a változó neve, nem string
//  port : 28300

class abstractNet : public QObject
{
    Q_OBJECT
public:
    virtual void setIP(QString, quint8)=0;

signals:
    void ServerNewMessage(Command *str);       //új bejövő üzenet klienstől signal
    void ClientNewMessage(Command *str);         //új bejövő üzenet szervertől signal

    void ServerSendMessage(Command *str);        //új üzenet kiküldése mindenkinek signal
    void ClientSendMessage(Command *str);        //új üzenet szervernek signal

    void finish();                              //kilépés signal

public slots:

};
