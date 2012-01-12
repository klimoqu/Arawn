#ifndef QARAWNWINDOW_HPP
#define QARAWNWINDOW_HPP

#include <QtGui>
#include "GUI/pixmapobjectitem.hpp"
#include "GUI/qgraphicsmenu.hpp"

class QArawnWindow : public QGraphicsView
{
    Q_OBJECT

public:
    QArawnWindow() {}

    void initWindow();

    QGraphicsScene *scene;

public slots:
    void initializeOthers();
    void showArawnScreen();
    void enterMenus();
    void playSound(uchar n);

private:
    inline void initializeMenus();
    void closeEvent(QCloseEvent *);

    QStateMachine *machine;
    QSound* sounds[15];

    PixmapObjectItem *pixWelcomeItem;
    PixmapObjectItem *pixFireItem;
    PixmapObjectItem *pixArawnItem;
    PixmapObjectItem *pixHirItem;

    QGraphicsTextItem *copyright;

    QState *stateLogo;
    QState *stateArawn;
    QState *stateMenu;
    QHistoryState *stateMenuHistory;
    QState *stateNetSettings;
    QState *statePlayerSetup;
    QState *stateMapSelection;
    QState *stateSurvivalCup;
    QState *stateMurderCup;
    QState *stateNetPlayerSetup;
    QState *stateNetSurvivalCup;
    QState *stateNetMurderCup;
    QState *stateAbout;
    QState *stateGame;
    QState *stateQuit;
    QFinalState *finalState;
};

#endif // QARAWNWINDOW_HPP










