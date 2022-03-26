#include "Collectable.hpp"
#include "Core.hpp"
#include "Entity.hpp"

struct room;
struct Porta;

enum{
    PORTA_SOPRA,
    PORTA_DESTA,
    PORTA_SOTTO,
    PORTA_SINISTRA
};

struct Porta{
    int posizione; //es PORTA_SINISTRA o PORTA_DESTA
    room *next_room;
};



struct item_node {
    Core item;
    Core *next;
};
typedef item_node *ListItem;

struct entity_node {
    Entity mob;
    Entity *next;
};
typedef entity_node *ListEntity;



struct room{
    ListItem items; //array degli elementi non vivi della stanza
    ListEntity entities;   //personaggi vivi
    Porta *porte[4]; // se la porta è NULL vuol dire che lì c'è un muro, se porta->next_room è NULL vuol dire che non è ancora stata creata la stanza sucessiva
};

struct Map{
    room *current_room;
    room *rooms; /* puntatore alla prima stanza, tutte le altre sono collegate dalle porte
                  * Porta linka a doppia direzione le stanze
                  */
};

// inizializza la mappa, restituisce un puntatore alla mappa il cui uso è facoltativo.
// quando la mappa viene inizializzata crea una stanza come quella in input.
Map *init_map(room stanza_iniziale);

//cambia la stanza in cui il personaggio si trova in quella passata per indirizzo dalla funzione
void change_room(room *new_room);


