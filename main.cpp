#include <QtGui/QApplication>

#include <fstream>

#include "GUI/qarawnwindow.hpp"
#include "map.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QArawnWindow w;

            Map *test=new Map(1);
            std::ofstream outputfile;
            outputfile.open("test");
            test->Save(std::cout);
            outputfile.close();


    w.showFullScreen();
    /*
      TODO:
      w.initializeWelcome();
      w.showWelcome();
      w.initializeArawnScreen();
      w.showArawnScreen();
      w.initializeMenus();
      w.showMainMenu();
    */
    return a.exec();
}
