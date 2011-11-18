/** ************************************************************************
 *
 *             Hir yw'r dydd a hir yw'r nos, a hir yw aros
 *                                 ARAWN
 *
 ***************************************************************************
 *
 *  Description: A bomberman game, inspired by Clanbomber
 *  Begin:       september 2011
 *  Version:
 *  Relased:
 *  Copyright:   Móréh Tamás, Klicsu Zsolt, Quintz Gábor
 *
 ***************************************************************************/


/** ************************************************************************
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 ***************************************************************************/


#include "qarawnapplication.hpp"
#include "GUI/qarawnwindow.hpp"
#include "map.hpp"

int main(int argc, char *argv[])
{
    QArawnApplication a(argc, argv);
    QArawnWindow w;

            /*
            Map *test=new Map(1);
            std::ofstream outputfile;
            outputfile.open("test");
            test->Save(std::cout);
            outputfile.close();
            */

    w.showFullScreen();
    /*
      TODO:
      w.initializeArawnScreen();
      w.showArawnScreen();
      w.initializeMenus(); // Utolsó init
      w.showMainMenu(); //-> innentől már szükség lesz az event loop-ra (a.exec();)
    */
    return a.exec();
}
