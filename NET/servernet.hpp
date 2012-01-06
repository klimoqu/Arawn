#pragma once
#include "NET/abstractNET.h"
#include <QtNetwork/QTcpServer>


class servernet:public abstractNet
{
    uchar playersnumber;


public:
    servernet(uchar playersnumber)
    {
        this->playersnumber=playersnumber;
    }
};
