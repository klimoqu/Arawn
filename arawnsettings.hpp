#ifndef ARAWNSETTINGS_HPP
#define ARAWNSETTINGS_HPP

#include "arawnheader.h"

class ArawnSettings
{
private:
    ArawnSettings();

    inline void load(QDataStream &stream);
    inline void save(QDataStream &stream);
    static ArawnSettings *aSettings;
    QString path;

public:
    static void create()
    {
        aSettings = new ArawnSettings;
    }

    static ArawnSettings* instance()
    {
        return aSettings;
    }

    QList<QPair<QString, QVariant> > languageValues;
    QVariant language;

    QList<QPair<QString, QVariant> > openGlRenderingValues;
    QVariant openGlRendering;

    QList<QPair<QString, QVariant> > showCorpsePartsValues;
    QVariant showCorpseParts;

    QList<QPair<QString, QVariant> > shakyExplosionValues;
    QVariant shakyExplosion;

    QList<QPair<QString, QVariant> > roundTimeDefaultValues;
    QVariant roundTimeDefault;

// Start/Max Extras
    QList<QPair<QString, QVariant> > startBombsValues;
    QVariant startBombs;

    QList<QPair<QString, QVariant> > maxBombsValues;
    QVariant maxBombs;

    QList<QPair<QString, QVariant> > startFireValues;
    QVariant startFire;

    QList<QPair<QString, QVariant> > maxFireValues;
    QVariant maxFire;

    QList<QPair<QString, QVariant> > startSpeedValues;
    QVariant startSpeed;

    QList<QPair<QString, QVariant> > maxSpeedValues;
    QVariant maxSpeed;

    QList<QPair<QString, QVariant> > startPushBombsValues;
    QVariant startPushBombs;

    QList<QPair<QString, QVariant> > enablePushBombsValues;
    QVariant enablePushBombs;

    QList<QPair<QString, QVariant> > startDropBombsValues;
    QVariant startDropBombs;

    QList<QPair<QString, QVariant> > enableDropBombsValues;
    QVariant enableDropBombs;

// Enable/Disable Diseases
    QList<QPair<QString, QVariant> > enableFailingBombsValues;
    QVariant enableFailingBombs;

    QList<QPair<QString, QVariant> > enableOppositeControlsValues;
    QVariant enableOppositeControls;

    QList<QPair<QString, QVariant> > enableInvisibilityValues;
    QVariant enableInvisibility;

// Bomb Timing and Speed
    QList<QPair<QString, QVariant> > bombSpeedValues;
    QVariant bombSpeed; // n/10 fields/seconds

    QList<QPair<QString, QVariant> > bombTimerValues;
    QVariant bombTimer; // 1/10 s

    QList<QPair<QString, QVariant> > resolutionValues;
    QVariant resolution;

    bool wideLayout;

// Player Names
    QVariant defaultPlayer1Name;
    QVariant defaultPlayer2Name;
    QVariant defaultPlayer3Name;
    QVariant defaultPlayer4Name;

};

#endif // ARAWNSETTINGS_HPP
