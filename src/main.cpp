#include <cstddef>
#include <iostream>
#include <ctime>
#include "Map.h"
#include "Player.hpp"
#include "Room.hpp"
#include "geometry.h"
#include "physics.h"
#include "Screen.hpp"
#include "Wall.hpp"
#include "Hostile.hpp"

#ifdef _WIN32 // sleep fn
#include <Windows.h>
#include <ncursesw/ncurses.h>
#else
#include <unistd.h>
#include <ncurses.h>
#endif

using namespace std;

#define FRAMETIME 30       // durata di un frame ~~> velocità del gioco
void controller(Player *); // gestisce la tastiera

void exit_game(); // permette di uscire

map *dummy_map;

char n[10] = "gino";
char n1[10] = "perino";
char n2[10] = "rubedo";
char n3[10] = "albedo";
char n4[10] = "jasmine";

char desc[20] = "giocatore";
char desc1[20] = "goblin";
char desc2[20] = "mago";
char desc3[20] = "ladro";
char desc4[20] = "napoletano";
char desc5[20] = "sasso";
char desc6[20] = "muro di pietra";

Hostile *villan = new Hostile(3, n1, 8, 5, {40, 15}, '*', desc1);
Hostile *villan1 = new Hostile(3, n2, 3, 5, {60, 7}, '=', desc2);
Hostile *villan2 = new Hostile(3, n3, 7, 5, {20, 10}, '$', desc3);
Hostile *villan3 = new Hostile(3, n4, 10, 5, {22, 4}, ')', desc4);
Core *rock = new Core({35, 7}, 'O', desc5);
Wall *w1 = new Wall({{ROOM_WIDTH / 2, ROOM_HEIGHT / 4}, false, ROOM_WIDTH / 4});
Wall *w2 = new Wall({{10, 25}, true, ROOM_HEIGHT / 4});


Player *player = new Player(10, 10, NULL, NULL, n, 6, 5, {20, 15}, '@', desc);
Screen schermo = Screen();

int main()
{
    // init schermo
    time_t inizio_frame, fine_frame;
    // init della mappa
    dummy_map = init_map(player);

    // aggiungo elementi alla stanza
    dummy_map->current_room->add_entity(villan);
    dummy_map->current_room->add_entity(villan1);
    dummy_map->current_room->add_entity(villan2);
    dummy_map->current_room->add_entity(villan3);
    dummy_map->current_room->add_Core(rock);
    dummy_map->current_room->add_wall(w2);
    //dummy_map->current_room->add_wall(w1);



    // game loop
    while (!game_over(*player))
    {
        inizio_frame = time(0);

        controller(player);

        // do_room(dummy_map->current_room);
        schermo.do_screen(dummy_map->current_room);

        fine_frame = time(0);
#ifdef _WIN32
        Sleep(FRAMETIME - (fine_frame - inizio_frame));
#else
        usleep(1000 * (FRAMETIME - (fine_frame - inizio_frame))); // usleep specifica quanti micro secondi sospendere l'esecuzione
#endif
    }
}

// https://stackoverflow.com/questions/4025891/create-a-function-to-check-for-key-press-in-unix-using-ncurses
void controller(Player *player)
{
    int key;
    do
    {
        key = getch();
        switch (key)
        {
        case 'w':
            player->move_up(dummy_map->current_room);
            break;
        case 'a':
            player->move_left(dummy_map->current_room);
            break;
        case 'd':
            player->move_right(dummy_map->current_room);
            break;
        case 's':
            player->move_down(dummy_map->current_room);
            break;
        case 'q':
            exit_game();
            break;
        default:
            break;
            // ...
        }
    } while (key != ERR); // finché ci sono tasti da leggere
}

void exit_game()
{
    schermo.stop_screen();
    // destroy_map(*dummy_map);
    exit(EXIT_SUCCESS);
}
