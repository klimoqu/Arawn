#ifndef QARAWNWINDOW_HPP
#define QARAWNWINDOW_HPP

#include <QtGui>
#include "pixmapobjectitem.hpp"
#include "qgraphicsmenu.hpp"
#include "graphicsmap.hpp"

class QArawnWindow : public QGraphicsView
{
    Q_OBJECT

public:
    QArawnWindow() {}

    void initWindow();

    QGraphicsScene *scene;

signals:
    void trRoom();

public slots:
    void initializeOthers();
    void showArawnScreen();
    void enterMenus();
    void enterGame();
    void finishGame();
    void playSound(uchar n);
    void startSurvival();
    void startMurder();

private:
    inline void initializeMenus();
    void closeEvent(QCloseEvent *);

    QStateMachine *machine;

    QSound* media[15];
    //Phonon::MediaObject* media[15];

    PixmapObjectItem *pixWelcomeItem;
    PixmapObjectItem *pixFireItem;
    PixmapObjectItem *pixArawnItem;
    PixmapObjectItem *pixHirItem;
    QPropertyAnimation *firAnim;
    QGraphicsTextItem *copyright;

    GraphicsMap *grMap;
    GraphicsTimer *grTimer;
    GraphicsCup *grCup;
    Cup* c;

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
};

#endif // QARAWNWINDOW_HPP










