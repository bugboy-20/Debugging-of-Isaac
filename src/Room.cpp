#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Core.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "List.hpp"
#include "RoomEvent.hpp"
#include "Wall.hpp"
#include "geometry.h"
Room::Room(int id, List walls, List entities, List cores) : Room(id, walls)
{

    this->entities = List(entities.head);
    this->core = List(cores.head);
}

Room::Room(int id, List walls)
{
    this->id = id;

    this->p = NULL;

    for (int i = 0; i < 4; i++)
        this->door[i] = NULL;

    this->entities = List();
    this->core = List();
    this->walls = List(walls.head);

    // this->events=Queue();
}

Room::Room(int id)
{
    this->id = id;

    this->p = NULL;

    for (int i = 0; i < 4; i++)
        this->door[i] = NULL;

    this->entities = List();
    this->core = List();
    this->walls = List();

    // this->events=Queue();
}

Core *Room::get_element_in_this_position(coords p)
{
    node *currentNode;
    Core *core_elm;

    if (this->p->get_x() == p.x && this->p->get_y() == p.y)
        return (Core *)this->p;

    for (currentNode = this->entities.head; currentNode != NULL; currentNode = currentNode->next)
    {
        core_elm = (Core *) currentNode->element;
        if (core_elm->get_x() == p.x && core_elm->get_y() == p.y)
            return (Core *) currentNode->element;
    }

    for (currentNode = this->core.head; currentNode != NULL; currentNode = currentNode->next)
    {
        core_elm = ((Core *)currentNode->element);
        if (core_elm->get_x() == p.x && core_elm->get_y() == p.y)
            return (Core *) currentNode->element;
    }

    for (currentNode = this->walls.head; currentNode != NULL; currentNode = currentNode->next)
    {
        Wall* w = (Wall*) currentNode->element;
        if (w->is_wall(p))
            return (Core *)currentNode->element;
    }
    return NULL;
}

int Room::get_id() { return this->id; }

void Room::add_Core(Core *e)
{
    this->core.push(e);
}

void Room::add_entity(Entity *e)
{
    this->entities.push(e);
}

void Room::add_wall(Wall *e) {
    this->walls.push(e);
}

void Room::delete_room_menber(Core *m)
{
    if (entities.delete_element(m))
        return;
    else if (core.delete_element(m))
        return;
    else
        walls.delete_element(m);
}

List Room::get_room_member(bool walls_too)
{
    List l = get_entities(true);
    List c = List(core.head);
    l.append(c);
    if (walls_too) {
        List w = List(walls.head);
        l.append(w);
    }
    return l;
}

List Room::get_entities(bool player_too)
{
    List l = List(entities.head);
    if (player_too)
        l.push(p);
    return l;
}

List Room::get_walls()
{
    return List(walls.head);
}

void Room::add_event(RoomEvent *e)
{
    this->events.enqueue((void *)e);
}

RoomEvent *Room::get_event()
{
    return (RoomEvent *)this->events.dequeue();
}
Room *Room::next_room(enum door_pos p) {
    if (this->door[p] != NULL)
        return this->door[p]->next_room;
    else {
        fprintf(stderr, "Errore: si è tentato di entrare per una porta inesistente\n");
        exit(EXIT_FAILURE);
    }
}


void Room::prinmt_room_menmb()
{
    for (node *member = entities.head; member != NULL; member = member->next)
    {
        std::cout << ((Entity *)member->element)->get_display() << std::endl;
    }
}
