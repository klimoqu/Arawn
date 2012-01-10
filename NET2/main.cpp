#include <QtCore/QCoreApplication>
#include "teszt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    teszt t;

    return a.exec();
}
