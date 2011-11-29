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

#include "arawnheader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QArawnWindow aWindow;
    aWindow.initWindow();
    aWindow.showFullScreen();

    QTimer timer;
    timer.setSingleShot(true);
    QObject::connect(&timer, SIGNAL(timeout()),
                     &aWindow, SLOT(showArawnScreen()));
    timer.start(2500);
    aWindow.initializeOthers();
    aWindow.initializeMenus();


  /*
    TODO:
      aWindow.initializeMenus(); // Utolsó init
      aWindow.showMainMenu(); //-> innentől már szükség lesz az event loop-ra (a.exec();)
    */
    return a.exec();
}










