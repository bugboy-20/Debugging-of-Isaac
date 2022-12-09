#pragma once
#include "Entity.hpp"
#include "Equipment.hpp"
#include "geometry.h"

struct inventory
{
    Item *items[player_inventory_slots];
    int item_n;
    Potion pots;
    Key keys;
};

class Player : public Entity
{
protected:
    int max_health;
    int score;
    inventory inv;

    // incrementa le statistiche del player se i valori sono positivi e le decrementa se sono negativi
    void add_stats(stats s);

public:
    Player(coords pos, char name[10], int max_health);
    Player(coords pos, char display, char description[], char name[10], int damage, int max_health);
    int get_max_health();
    int get_score();
    void set_health(int health);
    void change_health(int health);

    inventory get_inventory();
    // inserisce un item in uno slot preciso
    void add_item(int slot, Item *);
    // inserisce un item nel primo slot libero
    void add_item(Item *);

    // rimuove l'item nello slot indicato, se è presente
    Item *remove_item(int slot);
    // rimuove l'item se è presente
    Item *remove_item(Item *);

    // se la pozione passata come paramentro è di livello superiore faccio l'upgrade,
    // aggiungo il numero di utilizzi della pozione a quello del player
    // delloco il puntotatore alla pozione
    void add_potion(Room *, Potion *);
    // rimuove un utilizzo alle pozioni e se manca della vita al player lo cura
    void use_potion(Room *room);
    // aggiunge il numero di utilizzi della chiave alla chiave del player e delloca il puntatore passato in input
    void add_key(Room *, Key *);
    // rimuove un utilizzo alla chiave se ne ha, e restituisce se è stata usato oppure no
    bool use_key(Room *room);
};
