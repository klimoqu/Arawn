#ifndef QARAWNWINDOW_HPP
#define QARAWNWINDOW_HPP

#include "arawnheader.h"

struct ArawnSettings
{
    enum ArawnSettingsVersion
    {
        Current = 1
    };

    enum Language
    {
        English,
        Hungarian,
        German
    };


    uchar language;
    bool openGlRendering;
    bool showCorpseParts;
    bool shakyExplosion;
    ushort roundTimeDefault;
    uchar pointsToPlayOff;

    // Start/Max Extras
    uchar startBombs;
    uchar maxMoreBombs;
    uchar startFire;
    uchar maxMoreFire;
    uchar startSpeed;
    uchar maxMoreSpeed;
    bool startPushBombs;
    bool enablePushBombs;
    bool startDropBombs;
    bool enableDropBombs;

    // Enable/Disable Diseases
    bool enableFailingBombs;
    bool enableOppositeControls;
    bool enableInvisibility;

    // Bomb Timing and Speed
    uchar bombSpeed; // n/10 fields/seconds
    uchar bombTimer; // 1/10 s

    bool wideLayout;
    ushort screenX;
    ushort screenY;

    ArawnSettings() : language(English), openGlRendering(false), showCorpseParts(true),
        shakyExplosion(true), roundTimeDefault(60), pointsToPlayOff(10), startBombs(1),
        maxMoreBombs(8), startFire(1), maxMoreFire(8), startSpeed(1), maxMoreSpeed(5),
        startPushBombs(false), enablePushBombs(true), startDropBombs(false), enableDropBombs(true),
        enableFailingBombs(true), enableOppositeControls(true), enableInvisibility(true),
        bombSpeed(40), bombTimer(30)
    {
        wideLayout = false;
        screenX = 800;
        screenY = 600;
    }
};

static ArawnSettings aSettings;


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
    QGraphicsPixmapItem *welcomePixmap;

    QFont font;
    QSound* sounds[15];


};

#endif // QARAWNWINDOW_HPP










