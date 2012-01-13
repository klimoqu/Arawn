#ifndef QARAWNWINDOW_HPP
#define QARAWNWINDOW_HPP

#include <QtGui>
#include "GUI/pixmapobjectitem.hpp"
#include "GUI/qgraphicsmenu.hpp"
#include "GUI/graphicsmap.hpp"

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
    void enterGame();
    void finishGame();
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
    QPropertyAnimation *firAnim;
    QGraphicsTextItem *copyright;

    GraphicsMap *grMap;
    GraphicsTimer *grTimer;
    GraphicsCup *grCup;
    Game *g;

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
    QState *roomState;
    QState *stateNetSurvivalCup;
    QState *stateNetMurderCup;
    QState *stateAbout;
    QState *stateGame;
    QState *mapState;
    QState *cupState;
    QFinalState *gameFinal;
    QState *stateQuit;
    QFinalState *finalState;
};

#endif // QARAWNWINDOW_HPP










