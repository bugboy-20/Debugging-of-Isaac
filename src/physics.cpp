#include <cstddef>
#include <string.h>
#include <ctime>
#include <chrono>
#include "physics.h"
#include "Events.hpp"
#include "Hostile.hpp"
#include "Map.h"

using namespace std::chrono;
List bullets = List();

bool collision(int x, int y, Room& r)
{
    bool flag1, flag2, flag3;
    coords pos;

    pos.x = x;
    pos.y = y;
    flag1 = wall_collision(pos, r);
    flag2 = general_collision(pos, r);
    door_collision(pos, r);
    if(flag1 || flag2) return true;
    else return false;
}

bool wall_collision(coords pos, Room& r)
{
    if(pos.y < 1) return true;
    else if(pos.x < 1) return true;
    else if(pos.y > ROOM_HEIGHT - 2) return true;
    else if( pos.x > ROOM_WIDTH - 2) return true;
    else return false;
}

bool general_collision(coords pos, Room& r){
    if(r.get_element_in_this_position(pos) == NULL){
        return false;
    }else{
        return true;
    }
}

void door_collision(coords p, Room& r)
{
    if(p.x == 0 && p.y == (ROOM_HEIGHT/2) || p.x == 0 && p.y == (ROOM_HEIGHT/2) - 1){  

        if(next_room_position(r, LEFT_DOOR))  repos_player_in_new_room(p, r, LEFT_DOOR, RIGHT_DOOR);
           
    }else if(p.x == ROOM_WIDTH-1 && p.y == (ROOM_HEIGHT/2) || p.x ==  ROOM_WIDTH-1 && p.y == (ROOM_HEIGHT/2) - 1){
           
        if(next_room_position(r, RIGHT_DOOR))  repos_player_in_new_room(p, r, RIGHT_DOOR, LEFT_DOOR);

    }else if(p.x == ROOM_WIDTH/2 && p.y == 0 || p.x ==  (ROOM_WIDTH/2) - 1 && p.y == 0){

        if(next_room_position(r, UPPER_DOOR))  repos_player_in_new_room(p, r, UPPER_DOOR, LOWER_DOOR);

    }else if(p.x == ROOM_WIDTH/2 && p.y == (ROOM_HEIGHT-1) || p.x ==  (ROOM_WIDTH/2) - 1 && p.y == (ROOM_HEIGHT-1)){
            
        if(next_room_position(r, LOWER_DOOR))  repos_player_in_new_room(p, r, LOWER_DOOR, UPPER_DOOR);

    }
}

void repos_player_in_new_room(coords pos, Room& r, enum door_pos p, enum door_pos p1){
    coords old_pos, new_pos;
    if(pos.x == door_position(p)[0].x &&  pos.y == door_position(p)[0].y){
        old_pos = door_position(p)[0];
        new_pos = door_position2(p1)[0];
    }else{
        old_pos = door_position(p)[1];
        new_pos = door_position2(p1)[1];
    }
    r.next_room(p)->p->reposition(new_pos);
    r.next_room(p)->add_event(new EntityMoveE(old_pos, new_pos, r.next_room(p)->p->get_display()));
}

bool next_room_position(Room& r, enum door_pos p){
    if(r.door[p]!=NULL) {
        if(r.door[p]->next_room != NULL){
            change_room(r.next_room(p));
        }else{
            change_room(add_room(&r, p));
        }
        bullets.destroy();
        return true;
    }else return false;
}


void enemy_range(Room& r){
    List entities = r.get_entities(false);
    node *tmp = entities.head;
    while(tmp != NULL){
        Hostile *e = (Hostile*) tmp->element;
        bool enemy_range = (r.p->get_x() == e->get_x() && (r.p->get_y() <= e->get_y() + e->get_trigger_radius()) && (r.p->get_y() >= e->get_y()));
        if((enemy_range && time(0) - e->get_last_shot() >= e->get_attack_speed())){
            Bullet *b = new Bullet({e->get_x(), e->get_y()}, e->get_damage());
            bullets.push(b);
            e->set_last_shot(time(0));
        }    
        tmp = tmp->next;  
    }
    
    node *tmp_bullets = bullets.head;
    while(tmp_bullets != NULL){
        Bullet *b = (Bullet*) tmp_bullets->element;
        node *successivo = tmp_bullets->next;
        auto duration(duration_cast<milliseconds>(high_resolution_clock().now() - b->get_last_move()));
        if(duration.count() >= b->get_movement_speed()){
            if(!(b->move_down(&r))){
                if((b->get_y() + 1 == r.p->get_y() && b->get_x() == r.p->get_x())){
                    r.p->set_health(r.p->get_health() - b->get_damage());
                    r.add_event(new PlayerHealthChangedE(r.p));
                }         
                r.add_event(new EntityKilledE(b));
                bullets.delete_element(b);                                                        
            }
            b->set_last_move(high_resolution_clock().now());
        }
        tmp_bullets = tmp_bullets->next;      
    }     
}

void do_room(Room *r){enemy_range(*r);}; // fa cose sulla stanza

bool game_over(Player p)
{
    if(p.get_health()<=0) return true;     //il gioco termina quando finisce la vita 
    else return false;
}
