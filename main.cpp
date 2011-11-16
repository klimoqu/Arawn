#include <fstream>

#include "qarawnapplication.hpp"
#include "GUI/qarawnwindow.hpp"
#include "map.hpp"

int main(int argc, char *argv[])
{
    QArawnApplication a(argc, argv);
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
      w.initializeMenus(); // Utolsó init
      w.showMainMenu(); //-> innentől már szükség lesz az event loop-ra (a.exec();)
    */
    return a.exec();
}
