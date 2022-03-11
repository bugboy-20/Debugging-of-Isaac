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



struct item_node {
    Item mob;
    Item *next;
};
typedef Item *ListItem;

struct mob_node {
    Mob mob;
    Mob *next;
};
typedef Mob *ListMob;



struct room{
    ListItem items; //array degli elementi non vivi della stanza
    ListMob *mobs; //personaggi vivi
    Porta porte[4];
};

struct Map{
    room *current_room;
    room *rooms; /* puntatore alla prima stanza, tutte le altre sono collegate dalle porte
                    Porta linka a doppia direzione le stanze
                    */
};
