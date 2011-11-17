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

### QArawnApplication

Minden beállítás globális, azaz a `QApplication` leszármazott
`QArawnApplication` része. Ezt bárhonnan a programból a pl.
`qApp()->aSettings.resolution` hívással elérhetjük. További előnye, hogy
platformfüggetlenül szerializálhatjuk a beállítást, így a
`sReader >> aSettings;` sorra degradálódik az ÖSSZES beállítás betöltése.

Továbbá ebben az osztályban PLATFORMÉRZÉKENYEN létrejön a program könyvtára,
(nincs bajmolódás a registryvel), ahová a többi mentés is kerülhet.

    QDir dir(QDir::homePath() + "/AppData");
    if(!dir.exists("Arawn"))
        dir.mkdir("Arawn");

### QArawnWindow

Nevével ellentétben semmi köze a `QMainWindow`-hoz, de mivel minden QWidget
önállóan is meg tud jelenni, így a windows szintjén itt megjelenik egy
ablakhívás. A `QGraphicsView` képes egy `QGraphicsScene`-t megjeleníteni, így
a program ezen a szinten csak a Scene-ek váltogatásából fog állni. (Menü, Opciók, Játék, Eredmény).


