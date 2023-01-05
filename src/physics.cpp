#include <cstddef>
#include <iostream>
#include <string.h>
#include "physics.h"
#include "Events.hpp"
#include "Hostile.hpp"
#include "Map.h"
#include "time_handle.h"
#include "ItemOnGround.hpp"
using namespace std;
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
    if(r.get_element_in_this_position(pos) == NULL || r.get_element_in_this_position(pos)->is_crossable()){
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
    // r.next_room(p)->add_event(new EntityMoveE(old_pos, new_pos, r.next_room(p)->p->get_display()));
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
    timeval now;
    time_now(now);
    if(time_elapsed(e->get_last_shot(), now) >= e->get_attack_speed()){
        Bullet *b = new Bullet({e->get_x(), e->get_y()}, e->get_damage(), direction, e->get_range());
        bullets.push(b);
        time_now(now);
        e->set_last_shot(now);
    }
}

void damage_player(Room& r, Bullet *b){
    r.p->set_health(r.p->get_health() - b->get_damage());
    r.add_event(new PlayerHealthChangedE(r.p));
}

void entity_damage(Room& r, Bullet *b, Entity *e){
    e->set_health(e->get_health() - r.p->get_damage());   
    if(e->get_health() <= 0){
        if(((Hostile*) e)->get_drop() != NULL){
            ItemOnGround *i = new ItemOnGround({e->get_x(), e->get_y()}, ((Hostile*) e)->get_drop());
            r.add_items_on_ground(i);
            r.add_event(new ItemDroppedE({e->get_x(), e->get_y()}));
        }
        r.p->set_score(e->get_damage() + r.p->get_max_health());
        r.add_event(new ScoreChangedE(r.p));
        r.delete_room_menber(e);
        r.add_event(new EntityKilledE(e));
    }else r.add_event(new EntityDamagedE(e));
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
    return NULLO;
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
            {
                if(b->move_down(&r) == COLLISION){
                    if((b->get_y() + 1 == r.p->get_y() && b->get_x() == r.p->get_x())){
                        damage_player(r, b);
                    }else{
                        coords bpos = {b->get_x(), b->get_y() + 1};
                        if(r.get_element_in_this_position(bpos) != NULL && !r.get_element_in_this_position(bpos)->is_crossable() && is_entity(r, (Entity*)r.get_element_in_this_position(bpos))){
                            entity_damage(r, b, (Hostile*)r.get_element_in_this_position(bpos));
                        }
                    }
                    destroy_bullet(r, b);                                                     
                }
                break;
            }
            case UP:
                if(b->move_up(&r) == COLLISION){
                    if((b->get_y() - 1 == r.p->get_y() && b->get_x() == r.p->get_x())){
                        damage_player(r, b);
                    }else{
                        coords bpos = {b->get_x(), b->get_y() - 1};
                        if(r.get_element_in_this_position(bpos) != NULL && !r.get_element_in_this_position(bpos)->is_crossable() && is_entity(r, (Entity*)r.get_element_in_this_position(bpos))){
                            entity_damage(r, b, (Hostile*)r.get_element_in_this_position(bpos));
                        }
                    }      
                    destroy_bullet(r, b);                                                      
                }
                break;
            case RIGHT:
                if(b->move_right(&r) == COLLISION){
                    if((b->get_x() + 1 == r.p->get_x() && b->get_y() == r.p->get_y())){
                        damage_player(r, b);
                    }else{
                        coords bpos = {b->get_x() + 1, b->get_y()};
                        if(r.get_element_in_this_position(bpos) != NULL && !r.get_element_in_this_position(bpos)->is_crossable() && is_entity(r, (Entity*)r.get_element_in_this_position(bpos))){
                            entity_damage(r, b, (Hostile*)r.get_element_in_this_position(bpos));
                        }
                    }       
                    destroy_bullet(r, b);                                                  
                }
                break;
            case LEFT:
                if(b->move_left(&r) == COLLISION){
                    if((b->get_x() - 1 == r.p->get_x() && b->get_y() == r.p->get_y())){
                        damage_player(r, b);
                    }else{
                        coords bpos = {b->get_x() - 1, b->get_y()};
                            if(r.get_element_in_this_position(bpos) != NULL && !r.get_element_in_this_position(bpos)->is_crossable() && is_entity(r, (Entity*)r.get_element_in_this_position(bpos))){
                            entity_damage(r, b, (Hostile*)r.get_element_in_this_position(bpos));
                        }
                    }         
                    destroy_bullet(r, b);                                                         
                }
                break;
        } 
    }
}

bool is_entity(Room& r, Entity *entity){
    List entities = r.get_entities(false);
    node *tmp = entities.head;
    bool flag = false;
    while(tmp != NULL){
        Hostile *e = (Hostile*) tmp->element;
        if(e == entity) flag = true;
        tmp = tmp->next;  
    }
    return flag;
}

void bullets_push(Room& r){
    List entities = r.get_entities(false);
    node *tmp = entities.head;
    while(tmp != NULL){
        Hostile *e = (Hostile*) tmp->element;
        if(enemy_in_range(r, e)){
            direction temp = enemy_shot_direction(r, e);
            if(temp != NULLO)
                bullet_creation(e, temp);
        }
        tmp = tmp->next;  
    }
}

void bullet_movement(Room& r){
    node *tmp_bullets = bullets.head;        
    while(tmp_bullets != NULL){
        Bullet *b = (Bullet*) tmp_bullets->element;
        node *successivo = tmp_bullets->next;
        shoot_in_direction(r, b);
        tmp_bullets = successivo;      
    } 
}

void entities_movement(Room &r){
    List entities = r.get_entities(false);
    node *tmp = entities.head;
    int low_smartness = 0;

    while(tmp != NULL){
        Hostile *e = (Hostile*) tmp->element;
        timeval now;
        time_now(now);
        if(time_elapsed(e->get_last_move(), now) >= e->get_movement_speed()){ 
            if(e->get_smartness() == low_smartness){
                move_in_random_direction(r, e);
            }else move_in_player_direction(r, e);
            time_now(now);
            e->set_last_move(now);
        }
        tmp = tmp->next;
    }
}

void move_in_random_direction(Room &r, Hostile *e){
    int move = rand() % 4;
    switch (move){
    case 0:
        e->move_right(&r);
        break;
    case 1:
        e->move_left(&r);
        break;
    case 2:
        e->move_up(&r);
        break;
    case 3:
        e->move_down(&r);
        break;
    default:
        break;
    }
}

void move_in_player_direction(Room &r, Hostile *e){
    bool flag = enemy_in_range(r, e);
    if(e->get_x() < r.p->get_x() && !flag){
        if(e->move_right(&r) == COLLISION && !flag){
            if(e->move_down(&r) == COLLISION && !flag) e->move_up(&r);
        }
    }else if(e->get_x() > r.p->get_x() && !flag){
        if(e->move_left(&r) == COLLISION && !flag){
            if(e->move_up(&r) == COLLISION && !flag) e->move_down(&r);
        }
    }else if(e->get_y() > r.p->get_y() && !flag){
        if(e->move_up(&r) == COLLISION && !flag){
            if(e->move_right(&r) == COLLISION && !flag) e->move_left(&r);     
        }
    }else if(e->get_y() < r.p->get_y() && !flag){
        if(e->move_down(&r) == COLLISION && !flag){
            if(e->move_right(&r) == COLLISION && !flag) e->move_left(&r);
        }
    }
}

void collect_item_on_ground(Room &r){
    List items_on_ground = r.get_items_on_ground();
    node *items_tmp = items_on_ground.head;

    while(items_tmp != NULL){
        ItemOnGround *i = (ItemOnGround*)items_tmp->element;
        if(r.p->get_x() == i->get_x() && r.p->get_y() == i->get_y()){
            r.p->add_item(i->get_item());
            r.add_event(new InventoryChangedE);
            r.delete_room_menber(i);
            r.add_event(new RoomChangedE());
        }
        items_tmp = items_tmp->next;
    }
}

void drop_item(Room& r, int slot){
    Weapon *spada = new Weapon(item, '\\', r.p->get_inventory().items[slot]->get_description(), lvl5);
    int block = 0, max_blocks = 8;
    coords block_around_player[max_blocks]={
        {r.p->get_x(), r.p->get_y() - 1},
        {r.p->get_x(), r.p->get_y() + 1},
        {r.p->get_x() + 1, r.p->get_y()},
        {r.p->get_x() - 1, r.p->get_y()},
        {r.p->get_x() + 1, r.p->get_y() - 1},
        {r.p->get_x() - 1, r.p->get_y() - 1},
        {r.p->get_x() + 1, r.p->get_y() + 1},
        {r.p->get_x() - 1, r.p->get_y() + 1}
    };

    while(block < max_blocks){
        if(r.get_element_in_this_position(block_around_player[block]) == NULL && !wall_collision(block_around_player[block], r)){
            ItemOnGround *i = new ItemOnGround(block_around_player[block], spada);
            r.p->remove_item(slot);
            r.add_items_on_ground(i);
            r.add_event(new ItemDroppedE({i->get_x(), i->get_y()}));
            break;
        }
        block++;
    }
}

void do_room(Room *r){ // fa cose sulla stanza
    bullets_push(*r);
    bullet_movement(*r);
    entities_movement(*r);
    collect_item_on_ground(*r);
}; 

bool game_over(Player p)
{
    if(p.get_health()<=0) return true;     //il gioco termina quando finisce la vita 
    else return false;
}
