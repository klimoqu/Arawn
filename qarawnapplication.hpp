#ifndef QARAWNAPPLICATION_HPP
#define QARAWNAPPLICATION_HPP

#include <QtGui/QApplication>

class QArawnApplication : public QApplication
{
public:
    QArawnApplication(int argc, char *argv[]);
    bool writeSettings();



    enum Language
    {
        English,
        Hungarian,
        German
    };

    enum Resolution
    {
        // 4:3
        R800x600,
        R1024x768,
        R1280x1024,

        // 16:10
        R1280x800,
        R1440x900,
        R1680x1050,

        // 16:9
        R1280x720,
        R1366x768
    };

    // Settings to save and read with ~/.arawn/gamesettings
    struct ArawnSettings
    {
        Language language;
        Resolution resolution;
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

        // Default constructor
        ArawnSettings() : language(English), resolution(R800x600), showCorpseParts(true),
            shakyExplosion(true), roundTimeDefault(60), pointsToPlayOff(10), startBombs(1),
            maxMoreBombs(8), startFire(1), maxMoreFire(8), startSpeed(1), maxMoreSpeed(5),
            startPushBombs(false), enablePushBombs(true), startDropBombs(false), enableDropBombs(true),
            enableFailingBombs(true), enableOppositeControls(true), enableInvisibility(true),
            bombSpeed(40), bombTimer(30){}
    };



    ArawnSettings aSettings;
    QString path;
};

#endif // QARAWNAPPLICATION_HPP
