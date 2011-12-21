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

    QVariantMap languageValues;
    QVariant language;

    QVariantMap openGlRenderingValues;
    QVariant openGlRendering;

    QVariantMap showCorpsePartsValues;
    QVariant showCorpseParts;

    QVariantMap shakyExplosionValues;
    QVariant shakyExplosion;

    QVariantMap roundTimeDefaultValues;
    QVariant roundTimeDefault;

// Start/Max Extras
    QVariantMap startBombsValues;
    QVariant startBombs;

    QVariantMap maxBombsValues;
    QVariant maxBombs;

    QVariantMap startFireValues;
    QVariant startFire;

    QVariantMap maxFireValues;
    QVariant maxFire;

    QVariantMap startSpeedValues;
    QVariant startSpeed;

    QVariantMap maxSpeedValues;
    QVariant maxSpeed;

    QVariantMap startPushBombsValues;
    QVariant startPushBombs;

    QVariantMap enablePushBombsValues;
    QVariant enablePushBombs;

    QVariantMap startDropBombsValues;
    QVariant startDropBombs;

    QVariantMap enableDropBombsValues;
    QVariant enableDropBombs;

// Enable/Disable Diseases
    QVariantMap enableFailingBombsValues;
    QVariant enableFailingBombs;

    QVariantMap enableOppositeControlsValues;
    QVariant enableOppositeControls;

    QVariantMap enableInvisibilityValues;
    QVariant enableInvisibility;

// Bomb Timing and Speed
    QVariantMap bombSpeedValues;
    QVariant bombSpeed; // n/10 fields/seconds

    QVariantMap bombTimerValues;
    QVariant bombTimer; // 1/10 s

    QVariantMap resolutionValues;
    QVariant resolution;

    bool wideLayout;

// Player Names
    QVariant defaultPlayer1Name;
    QVariant defaultPlayer2Name;
    QVariant defaultPlayer3Name;
    QVariant defaultPlayer4Name;

};

#endif // ARAWNSETTINGS_HPP
