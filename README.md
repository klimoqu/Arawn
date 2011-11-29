ARAWN README -> Mivel ritkán találkozunk
========================================

Címsor 1.
---------

Folytonos szövegben `fix.szélességű()` kód.

### Címsor 2.

Részletesebb kifejtéshez:

    kódrészlet{
        kód()
    }

Változtatásaim áttekintése -morta
---------------------------------

### ArawnSettings

Tartalmazza az összes beállítást, ami a program működését befolyásolja.
Mostantól tetszőleges képernyőfelbontással működik, de a layout tulajdonság
nem menthető, az MINDIG a képernyőfelbontás arányából számítódik ki.
Szerializálva íródik fájlba, egy verzió flaggel ellátva, így később is
betölthetőek lesznek az elavult `gamesettings` fájlok.

### QArawnWindow

Nevével ellentétben semmi köze a `QMainWindow`-hoz, de mivel minden QWidget
önállóan is meg tud jelenni, így a windows szintjén itt megjelenik egy
ablakhívás.

Létrejöttekor betölti a mentett beállításokat, vagy létrehozza azokat a
képernyő felbontásásnak megfelelően. Egy `scene`-t használ, ezeken cserélődnek
és animálódnak az `Item`-ek.

Az `initializeOthers` nem csinál mást, csak betölti az összes olyan elemet, amikre
a programban végig szükség lesz. Minden `QObject` leszármazott tartalmazza a `this`
paramétert, így nem kell destruktort írni, rekurzívan törlődik minden.

A `showArawnScreen` példaértékű eljárás. Helyben jön létre minden, ami
a logók megjelenéséhez és az animációhoz kell, de még a jelenet befejezése előtt
elhagyjuk a blokkot. A szülő paraméterek miatt ezt megtehetjük, minden
törlődni fog, miután már nincs rá szükség.

















