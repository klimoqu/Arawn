#ifndef QARAWNWINDOW_HPP
#define QARAWNWINDOW_HPP

#include "arawnheader.h"

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
    void initializeMenus();
    void showMainMenu();

private:
    void setRenderingSystem();
    //void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);

    QString path;
    QGraphicsScene *scene;
    QStateMachine *machine;
    QSound* sounds[15];

    QGraphicsPixmapItem *pixWelcomeItem;
    QGraphicsPixmapItem *pixFireItem;
    QGraphicsPixmapItem *pixArawnItem;
    QGraphicsPixmapItem *pixHirItem;


    QState *stateLogo;
    QState *stateArawn;
    QState *stateMainMenu;
    QState *stateOptionsMenu;
};

#endif // QARAWNWINDOW_HPP










