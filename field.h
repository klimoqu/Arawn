#ifndef FIELD_H
#define FIELD_H

#include <QObject>

class field : public QObject
{
    bool blastable;
    bool permeable;
public:
    field(int id);
};

#endif // FIELD_H
