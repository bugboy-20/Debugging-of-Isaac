#include <cstddef>
#include <iostream>
#include <ctime>
#include "Screen.hpp"
#include "Map.h"
#include "Player.hpp"
#include "Room.h"
#include "geometry.h"
#include "physics.h"

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

void exit_game(); //permette di uscire

map *dummy_map;

char n[10] = "gino";
Player *player = new Player(10, 10, NULL, NULL, n, 6, 5, {20, 15}, '@');
Screen schermo = Screen();

int main()
{
    // init schermo
    time_t inizio_frame, fine_frame;
    // init della mappa
    dummy_map = init_map(player);
    // init del player

    // game loop
    while (!game_over())
    {
        inizio_frame = time(0);

        controller(player);
        // printw("(%d,%d)", player.getX(), player.getY());

        // do_room(dummy_map->current_room);
        schermo.render_room(*dummy_map->current_room);

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
            player->move_up(*dummy_map->current_room);
            break;
        case 'a':
            player->move_left(*dummy_map->current_room);
            break;
        case 'd':
            player->move_right(*dummy_map->current_room);
            break;
        case 's':
            player->move_down(*dummy_map->current_room);
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


void exit_game() {
    schermo.stop_screen();
    //destroy_map(*dummy_map);
    exit(EXIT_SUCCESS);
}
