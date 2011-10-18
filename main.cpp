#include <QtGui/QApplication>

#include <fstream>

#include "arawnwindow.hpp"
#include "map.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArawnWindow w;
    Map *test=new Map(1);
    std::ofstream outputfile;
    outputfile.open("test");
    test->Save(outputfile);
    outputfile.close();
    w.show();
    return a.exec();
}
