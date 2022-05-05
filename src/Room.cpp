#include <cstddef>
#include "Core.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Room.h"
#include "Room.hpp"
#include "List.hpp"
#include "geometry.h"
Room::Room(int id, List entities, List cores) : Room(id) {

    this->entities=List(entities);
    this->core=List(cores);

}

Room::Room(int id) {
    this->id=id;

    this->p=NULL;

    for (int i=0; i<4; i++)
        this->door[i]=NULL;

    this->entities=List();
    this->core=List();
    this->walls=List();

    //this->events=Queue();

}


Core* Room::get_element_in_this_position(coords p) {
    node *currentNode;
    Core *core_elm;

    for( currentNode=this->entities.head; currentNode!=NULL; currentNode=currentNode->next) {
        core_elm = ((Core*) currentNode->element);
        if (core_elm->getX() == p.x && core_elm->getY() == p.y) return (Core*) currentNode->element;
    }

    for( currentNode=this->core.head; currentNode!=NULL; currentNode=currentNode->next) {
        core_elm = ((Core*) currentNode->element);
        if (core_elm->getX() == p.x && core_elm->getY() == p.y) return (Core*) currentNode->element;
    }

    for( currentNode=this->walls.head; currentNode!=NULL; currentNode=currentNode->next) {
        core_elm = ((Core*) currentNode->element);
        if (core_elm->getX() == p.x && core_elm->getY() == p.y) return (Core*) currentNode->element;
    }
    return NULL;
}

int Room::get_id() { return this->id; }

void Room::add_Core(Core *e) {
    this->core.push(e);
}

void Room::add_entity(Entity *e) {
    this->entities.push(e);
}

void Room::delete_room_menber(Core *m) {
    if (entities.delete_element(m)) return;
    else if (core.delete_element(m)) return;
    else walls.delete_element(m);

}

List Room::get_room_member() {
    List l = get_entities(true);
    List c = List(core.head);
    List w = List(walls.head);
    l.append(c);
    l.append(w);
    return l;
}

List Room::get_entities(bool player_too) {
    List l = List(entities.head);
    if (player_too)
        l.push(p);
    return l;
}


List Room::get_walls() {
    return List(walls.head);
}

//Room *Room::next_room(enum door_pos) {} problemi da risolvere con Room.h
