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
    flag1 = wall_collision({x, y}, r);
    flag2 = entity_collision({x, y}, r);
    if(player_in_door(x, y, r)) door_collision({x, y}, r);
    if(flag1 || flag2) return true;
    else return false;
}

bool player_in_door(int x, int y, Room& r){
    bool flag = (r.p->get_x() == x - 1 && r.p->get_y() == y) 
                || (r.p->get_x() == x + 1 && r.p->get_y() == y)
                || (r.p->get_x() == x && r.p->get_y() == y - 1) 
                || (r.p->get_x() == x && r.p->get_y() == y + 1) ;
    
    return flag;
}

bool wall_collision(coords pos, Room& r)
{
    if(pos.y < 1) return true;
    else if(pos.x < 1) return true;
    else if(pos.y > ROOM_HEIGHT - 2) return true;
    else if( pos.x > ROOM_WIDTH - 2) return true;
    else return false;
}

bool entity_collision(coords pos, Room& r){
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

void bullet_creation(Entity *e, enum direction direction){
    if(time(0) - e->get_last_shot() >= e->get_attack_speed()){
        Bullet *b = new Bullet({e->get_x(), e->get_y()}, e->get_damage());
        b->set_direction(direction);
        bullets.push(b);
        e->set_last_shot(time(0));
    }
}

void player_damage(Room& r, Bullet *b){
    r.p->set_health(r.p->get_health() - b->get_damage());
    r.add_event(new PlayerHealthChangedE(r.p));
}

void entity_damage(Room& r, Bullet *b, Entity *e){
    e->set_health(e->get_health() - r.p->get_damage());
    r.add_event(new EntityDamagedE(e));
    if(e->get_health() <= 0){
        r.add_event(new EntityKilledE(e));
    }
}

void destroy_bullet(Room& r, Bullet *b){
    r.add_event(new EntityKilledE(b));
    bullets.delete_element(b); 
}

enum direction enemy_shot_direction(Room& r, Hostile *e){
    bool enemy_range_down = (r.p->get_x() == e->get_x() && (r.p->get_y() <= e->get_y() + e->get_trigger_radius()) && (r.p->get_y() >= e->get_y()));
    bool enemy_range_up = (r.p->get_x() == e->get_x() && (r.p->get_y() >= e->get_y() - e->get_trigger_radius()) && (r.p->get_y() <= e->get_y()));
    bool enemy_range_right = (r.p->get_y() == e->get_y() && (r.p->get_x() <= e->get_x() + e->get_trigger_radius()+ 2) && (r.p->get_x() >= e->get_x()));
    bool enemy_range_left = (r.p->get_y() == e->get_y() && (r.p->get_x() >= e->get_x() - e->get_trigger_radius() - 2) && (r.p->get_x() <= e->get_x()));
    
    if(enemy_range_down) return DOWN;
    else if(enemy_range_up) return UP;
    else if(enemy_range_right) return RIGHT;
    else if(enemy_range_left) return LEFT;
}

bool enemy_in_range(Room& r, Hostile *e){
    bool enemy_in_range = (r.p->get_x() == e->get_x() && (r.p->get_y() <= e->get_y() + e->get_trigger_radius()) && (r.p->get_y() >= e->get_y()))
    || (r.p->get_x() == e->get_x() && (r.p->get_y() >= e->get_y() - e->get_trigger_radius()) && (r.p->get_y() <= e->get_y()))
    || (r.p->get_y() == e->get_y() && (r.p->get_x() <= e->get_x() + e->get_trigger_radius()+ 2) && (r.p->get_x() >= e->get_x()))
    || (r.p->get_y() == e->get_y() && (r.p->get_x() >= e->get_x() - e->get_trigger_radius() - 2) && (r.p->get_x() <= e->get_x()));
    
    return enemy_in_range;
}

void shoot_in_direction(Room& r, Bullet *b){
    if(b->get_direction() >= 0 && b->get_direction() <= 3){
        switch(b->get_direction()){
            case DOWN:
                if(!(b->move_down(&r))){
                    if((b->get_y() + 1 == r.p->get_y() && b->get_x() == r.p->get_x())){
                        player_damage(r, b);
                    }
                    destroy_bullet(r, b);                                                     
                }
                break;
            case UP:
                if(!(b->move_up(&r))){
                    if((b->get_y() - 1 == r.p->get_y() && b->get_x() == r.p->get_x())){
                        player_damage(r, b);
                    }       
                    destroy_bullet(r, b);                                                      
                }
                break;
            case RIGHT:
                if(!(b->move_right(&r))){
                    if((b->get_x() + 1 == r.p->get_x() && b->get_y() == r.p->get_y())){
                        player_damage(r, b);
                    }       
                    destroy_bullet(r, b);                                                  
                }
                break;
            case LEFT:
                if(!(b->move_left(&r))){
                    if((b->get_x() - 1 == r.p->get_x() && b->get_y() == r.p->get_y())){
                        player_damage(r, b);
                    }         
                    destroy_bullet(r, b);                                                         
                }
                break;
        } 
        b->set_last_move(high_resolution_clock().now());  
    }
}

void bullets_push(Room& r){
    List entities = r.get_entities(false);
    node *tmp = entities.head;
    while(tmp != NULL){
        Hostile *e = (Hostile*) tmp->element;
        if(enemy_in_range(r, e)){
            bullet_creation(e, enemy_shot_direction(r, e));
        }
        tmp = tmp->next;  
    }
}

void bullet_movement(Room& r){
    node *tmp_bullets = bullets.head;        
    while(tmp_bullets != NULL){
        Bullet *b = (Bullet*) tmp_bullets->element;
        node *successivo = tmp_bullets->next;
        auto duration(duration_cast<milliseconds>(high_resolution_clock().now() - b->get_last_move()));
        if(duration.count() >= b->get_movement_speed()){
            shoot_in_direction(r, b);
        }
        tmp_bullets = successivo;      
    } 
}

void do_room(Room *r){ // fa cose sulla stanza
    bullets_push(*r);
    bullet_movement(*r);
}; 

bool game_over(Player p)
{
    if(p.get_health()<=0) return true;     //il gioco termina quando finisce la vita 
    else return false;
}
