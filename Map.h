#include "Collectable.hpp"
#include "Item.hpp"
#include "Mob.hpp"

struct room;
struct Porta;

enum{
    PORTA_SOPRA,
    PORTA_DESTA,
    PORTA_SOTTO,
    PORTA_SINISTRA
};

struct Porta{ //dovrebbe essere un oggetto?
    int posizione; //es PORTA_SINISTRA o PORTA_DESTA
    room *next_room;
};

struct room{
    Item *items; //array degli elementi non vivi della stanza
    Mob *mobs; //personaggi vivi
    Porta porte[4];
};

struct Map{
    room *current_room;
    room rooms[];
};
