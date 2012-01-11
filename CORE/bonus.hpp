#pragma once

#include <QObject>
/*
  1 bomba erő növelése
  2 bomba erő csökkentése
  3 bombák számának növelése
  4 bombák számának csökkentése
  5 sebesség növelés
  6 sebesség csökkentés
  7 láthatatlanság
  8 ellenkező írány
  9 besülés
*/
class Bonus : public QObject
{
    Q_OBJECT
    uchar type;
    bool visible,usable;
public:
    Bonus(uchar type);
signals:

public slots:

};
