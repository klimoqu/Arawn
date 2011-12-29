ARAWN README
========================================


Eseménykezelés -morta
---------------------------------

"De jure" eseménykezelés nincs. `KeyEventTransition`-ok vannak,
amelyek egy adott `State`-hez tartoznak. Fontos változás tegnap óta,
hogy az egyéb reakciók (pl. hang) soha sincs közvetlenül bekötve
az eseményre, hanem a feldolgozó osztály küld egy visszszignált,
ha tényleg szükség van rá. Így tényleges, érzékelhető reakció /
állapotváltozás csak a bekötött `SignalTransition`-okból van.

Menü
----

A Menü immár bugmentes, szép, gyors. Még a menüváltás hangjait
és a hiányzó állapotokat kell megcsinálni. Ez utóbbinál már elengedhetetlen
a közös munka, hisz a hálózati/helyi játék bekonfigurálásáról van szó.

### Hálózati játék

Hogy nézzen ki a menü? Milyen beállítások kellenek? Hogy indítsa
a szervert?

Címsor 1.
---------

Folytonos szövegben `fix.szélességű()` kód.

### Címsor 2.

Részletesebb kifejtéshez:

    kódrészlet{
        kód()
    }













