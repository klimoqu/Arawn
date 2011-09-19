#include <QtGui/QApplication>
#include "arawnwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArawnWindow w;
    w.show();

    return a.exec();
}
