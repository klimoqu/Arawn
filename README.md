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


Címsor 1.
---------

Folytonos szövegben `fix.szélességű()` kód.

### Címsor 2.

Részletesebb kifejtéshez:

    kódrészlet{
        kód()
    }













