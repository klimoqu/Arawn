#ifndef QARAWNAPPLICATION_HPP
#define QARAWNAPPLICATION_HPP

#include <QtGui/QApplication>

class QArawnApplication : public QApplication
{
public:
    QArawnApplication(int argc, char *argv[]);

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
        Language language = English;
        Resolution resolution = R800x600;
        bool showCorpseParts = true;
        bool shakyExplosion = true;
        ushort roundTimeDefault = 60;
        uchar pointsToPlayOff = 10;

        // Start/Max Extras
        uchar startBombs = 1;
        uchar maxMoreBombs = 8;
        uchar startFire = 1;
        uchar maxMoreFire = 8;
        uchar startSpeed = 1;
        uchar maxMoreSpeed = 5;
        bool startPushBombs = false;
        bool enablePushBombs = true;
        bool startDropBombs = false;
        bool enableDropBombs = true;

        // Enable/Disable Diseases
        bool enableFailingBombs = true;
        bool enableOppositeControls = true;
        bool enableInvisibility = true;

        // Bomb Timing and Speed
        uchar bombSpeed = 40; // n/10 fields/seconds
        uchar bombTimer = 30; // 1/10 s
    };

    ArawnSettings aSettings;
    QString path;
};

#endif // QARAWNAPPLICATION_HPP
