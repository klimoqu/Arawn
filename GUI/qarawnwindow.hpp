#ifndef QARAWNWINDOW_HPP
#define QARAWNWINDOW_HPP

#include "arawnheader.h"

class PixmapObjectItem;
class GraphicsMenu;
class GraphicsAbout;

class QArawnWindow : public QGraphicsView
{
    Q_OBJECT

public:
    QArawnWindow() {}

    void initWindow();

signals:

public slots:
    void initializeOthers();
    void showArawnScreen();
    void enterMenus();
    void playSound(uchar n);

private:
    inline void initializeMenus();
    void closeEvent(QCloseEvent *);

    QGraphicsScene *scene;
    QStateMachine *machine;
    QSound* sounds[15];

    PixmapObjectItem *pixWelcomeItem;
    PixmapObjectItem *pixFireItem;
    PixmapObjectItem *pixArawnItem;
    PixmapObjectItem *pixHirItem;

    QGraphicsTextItem *copyright;

    GraphicsMenu *menuMain;
        GraphicsMenu *menuLocalGame;
            GraphicsMenu *menuGameSettings;
            GraphicsMenu *menuSMExtras;
            GraphicsMenu *menuEDDiseases;
        GraphicsMenu *menuNetworkGame;
            GraphicsMenu *menuCreateNetwork;
        GraphicsMenu *menuOptions;
        GraphicsAbout *aboutItem;

    QState *stateLogo;
    QState *stateArawn;
    QState *stateMainMenu;
        QState *stateLocalGameMenu;
            QState *statePlayerSetup; // TODO
            QState *stateMapSelection; // TODO
            QState *stateGameSettings;
            QState *stateSMExtras;
            QState *stateEDDiseases;
            QState *stateLoad; /** TODO Itt még át kell gondolni */
        QState *stateNetworkGameMenu;
            QState *stateCreateNetwork;
            /** TODO Szintén */
        QState *stateOptionsMenu;
        QState *stateMapEditor; // TODO
        QState *stateAbout; // TODO
        QFinalState *finalState;
};

#endif // QARAWNWINDOW_HPP










