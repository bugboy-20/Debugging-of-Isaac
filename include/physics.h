#pragma once
#include "Player.hpp"
#include "Room.hpp"
#include "Bullet.hpp"
#include "Hostile.hpp"

//Richiama le funzioni che gestiscono le collisioni del player 
bool collision(int x, int y, Room& r);

/*Funzione che controlla che ciò che vuole attraversare una porta
sia il player, e non altre entità (e.g. un proiettile)*/
bool player_in_door(coords pos, Room& r);

/*Funzione che si occupa di gestire le collisioni con le mura
esterne della mappa*/
bool wall_collision(coords pos, Room& r);

/*Funzione che si occupa di gestire le collisioni con le 
entità presenti nella mappa*/
bool entity_collision(coords pos, Room& r);

/*Funzione che si occupa di gestire la collisione con le porte
della mappa, e quindi di richiamare le funzioni per poter
effettuare il cambio della stanza*/
void door_collision(coords pos, Room& r);

/*Funzione che si occupa di controllare che la stanza in cui
il player vuole andare esista, e in caso affermativo effettua
trasferimento. Inoltre, distrugge la lista di proiettili della 
stanza precedente*/
bool next_room_position(Room& r, enum door_pos p);

/*Funzione che si occupa di riposizionare il player nella
nuova stanza visitata, in prossimità della porta corretta*/
void repos_player_in_new_room(coords pos, Room& r, enum door_pos p, enum door_pos p1);

/*Funzione che si occupa di gestire il danno subito dal player,
sottraendo la corretta quantità di punti di vita*/
void damage_player(Room& r, Bullet *b);

/*Funzione che si occupa di gestire il danno subito dai nemici,
sottraendo la corretta quantità di punti di vita*/
void entity_damage(Room& r, Bullet *b, Entity *e);

/*Funzione che si occupa di creare un proiettile e inserirlo
nella lista di proiettili*/
void bullet_creation(Entity *e, enum direction direction);

/*Funzione che si occupa di rimuovere il proiettile una volta
che collide*/
void destroy_bullet(Room& r, Bullet *b);

/*Funzione che si occupa di determinare se il player si trova 
nel trigger_radius di un nemico*/
bool enemy_in_range(Room& r, Hostile *e);

/*Funzione che effettua lo sparo del proiettile*/
void shoot_in_direction(Room& r, Bullet *b);

/*Funzione che si occupa di determinare la direzione in cui deve essere
sparato il proiettile*/
enum direction enemy_shot_direction(Room& r, Hostile *e);

//Funzione che controlla se l'entità passata in input è un nemico
bool is_entity(Room& r, Entity *entity);

/*Funzione che gestisce lo sparo di un proiettile*/
void bullets_push(Room& r);

/*Funzione che gestisce i proiettili in movimento*/
void bullet_movement(Room& r);

//Funzione che sceglie il movimento del nemico in base alla sua intelligenza
void entities_movement(Room &r);

//Funzione che fa muovere un nemico verso il player
void move_in_player_direction(Room &r, Hostile *e);

//Funzione che fa muovere un nemico in maniera casuale
void move_in_random_direction(Room &r, Hostile *e);

//Funzione per raccogliere gli item da terra
void collect_item_on_ground(Room &r);

//Funzione per rilasciare gli item dall'inventario
void drop_item(Room& r, int slot);

// fa cose sulla stanza
void do_room(Room *r); 

/*Funzione che controlla se il player ha finito la vita per
dichiarare l'eventyale game_over*/
bool game_over(Player p);
