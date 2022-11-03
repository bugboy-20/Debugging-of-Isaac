#include <cstddef>
#include <iostream>
#include <ctime>
#include "time_handle.h"
#include "Map.h"
#include "Player.hpp"
#include "Room.hpp"
#include "geometry.h"
#include "physics.h"
#include "Screen.hpp"
#include "Wall.hpp"
#include "Hostile.hpp"
#include "HostileList.hpp"

#ifdef _WIN32 // sleep fn
#include <Windows.h>
#include <ncursesw/ncurses.h>
#else
#include <unistd.h>
#include <ncurses.h>
#endif

using namespace std;

#define FRAMETIME 30       // durata di un frame ~~> velocità del gioco
#define utom(x) (1000 * x) // from micro to milli
//#define sleep_time(ti,tf) (FRAMETIME - (tf - ti))
int sleep_time(timeval start, timeval end);
void controller(Player *); // gestisce la tastiera

void exit_game(); // permette di uscire

map *dummy_map;

char n[10] = "gino";
char desc5[20] = "sasso";


Zombie *z = new Zombie({45, 15});
Slime *slime = new Slime({40, 15});
Scheletro *scheleton = new Scheletro({60, 7});
Goblin *goblin = new Goblin({20, 10});
Fantasma *fantasma = new Fantasma({22, 4});
Core *rock = new Core({35, 7}, 'O', desc5);
Wall *w1 = new Wall({{ROOM_WIDTH / 2, ROOM_HEIGHT / 4}, false, ROOM_WIDTH / 4});
Wall *w2 = new Wall({{10, 7}, true, ROOM_HEIGHT / 4});

Player *player = new Player({20, 15}, n, 10, NULL, NULL);
Screen schermo = Screen();

int main()
{
    // init schermo
    timeval inizio_frame, fine_frame;
    // init della mappa
    dummy_map = init_map(player);

    // aggiungo elementi alla stanza
    dummy_map->current_room->add_entity(slime);
    dummy_map->current_room->add_entity(scheleton);
    dummy_map->current_room->add_entity(goblin);
    dummy_map->current_room->add_entity(fantasma);
    dummy_map->current_room->add_entity(z);
    dummy_map->current_room->add_Core(rock);
    dummy_map->current_room->add_wall(w2);
    //dummy_map->current_room->add_wall(w1);



    // game loop
    while (!game_over(*player))
    {
        // il secondo parametro è la timezone, non importa usare quella giusta basta che sia uguale ovunque
        time_now(inizio_frame);

        controller(player);

        do_room(dummy_map->current_room);
        schermo.do_screen(dummy_map->current_room);

        time_now(fine_frame);
#ifdef _WIN32
        Sleep(sleep_time(inizio_frame,fine_frame));
#else
        usleep(utom(sleep_time(inizio_frame, fine_frame))); // usleep specifica quanti micro secondi sospendere l'esecuzione
#endif
    }

    exit_game();
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
        case KEY_UP:
            bullet_creation(player, UP);
            break;
        case KEY_DOWN:
            bullet_creation(player, DOWN);
            break;
        case KEY_RIGHT:
            bullet_creation(player, RIGHT);
            break;
        case KEY_LEFT:
            bullet_creation(player, LEFT);
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

int sleep_time(timeval start, timeval end){
    time_t te = time_elapsed(start, end);
    if(te > FRAMETIME) return 0;
    return FRAMETIME - te;
}