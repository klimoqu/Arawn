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

Törölve.

### QArawnWindow

Nevével ellentétben semmi köze a `QMainWindow`-hoz, de mivel minden QWidget
önállóan is meg tud jelenni, így a windows szintjén itt megjelenik egy
ablakhívás. A `QGraphicsView` képes egy `QGraphicsScene`-t megjeleníteni, így
a program ezen a szinten csak a Scene-ek váltogatásából fog állni. (Menü, Opciók, Játék, Eredmény).

Létrejöttekor betölti a mentett beállításokat, és a leendő elrendezést a felbontáshoz optimalizálja.
Beállítja a Scene-t az üdvözlőképrenyőre.
