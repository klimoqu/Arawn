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
    void playSound(uchar n);
    void showMainMenu();

private:
    inline void initializeMenus();
    //void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);

    QString path;
    QGraphicsScene *scene;
    QStateMachine *machine;
    QSound* sounds[15];

    PixmapObjectItem *pixWelcomeItem;
    PixmapObjectItem *pixFireItem;
    PixmapObjectItem *pixArawnItem;
    PixmapObjectItem *pixHirItem;

    GraphicsMenu *menuMain;
        GraphicsMenu *menuLocalGame;
            GraphicsMenu *menuGameSettings;
            GraphicsMenu *menuSMExtras;
            GraphicsMenu *menuEDExtras;
        GraphicsMenu *menuNetworkGame;
        GraphicsMenu *menuOptions;

    QState *stateLogo;
    QState *stateArawn;
    QState *stateMainMenu;
    QState *stateOptionsMenu;
};

#endif // QARAWNWINDOW_HPP










