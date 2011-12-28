#ifndef QARAWNWINDOW_HPP
#define QARAWNWINDOW_HPP

#include "arawnheader.h"

class PixmapObjectItem;
class GraphicsMenu;

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
    void close();

private:
    inline void initializeMenus();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

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
        GraphicsMenu *menuOptions;

    QState *stateLogo;
    QState *stateArawn;
    QState *stateMainMenu;
        QState *stateLocalGameMenu;
            QState *statePlayerSetup;
            QState *stateMapSelection;
            QState *stateGameSettings;
            QState *stateSMExtras;
            QState *stateEDDiseases;
            QState *stateLoad; /** TODO Itt még át kell gondolni */
        QState *stateNetworkGameMenu;
            /** TODO Szintén */
        QState *stateOptionsMenu;
        QState *stateMapEditor;
        QState *stateAbout;
        QFinalState *finalState;
};

#endif // QARAWNWINDOW_HPP










