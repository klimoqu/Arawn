#pragma once

#include <QObject>

class Bonus : public QObject
{
    Q_OBJECT
    uchar type;
public:
    Bonus(uchar type);
signals:

public slots:

};
