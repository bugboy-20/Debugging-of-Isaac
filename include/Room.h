#ifndef ROOM_H
#define ROOM_H

#include "Core.hpp"
#include "Entity.hpp"

struct room;
struct door;

enum
{
    UPPER_DOOR,
    RIGHT_DOOR,
    LOWER_DOOR,
    LEFT_DOOR
};

struct door
{
    int position; // es LEFT_DOOR o RIGHT_DOOR
    room *next_room;
};

struct item_node
{
    Core item;
    item_node *next;
};
typedef item_node *ListItem;

struct entity_node
{
    Entity *mob;
    entity_node *next;
};
typedef entity_node *ListEntity;

struct room
{
    ListItem items;      // array degli elementi non vivi della stanza
    ListEntity entities; // personaggi vivi
    door *doors[4];      // se la porta è NULL vuol dire che lì c'è un muro, se porta->next_room è NULL vuol dire che non è ancora stata creata la stanza sucessiva
};

#endif
