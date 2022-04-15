#include <time.h>
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

#define FRAMETIME 30       // durata di un frame ~~ velocità del gioco
void controller(Player *); // è solamente dimostrativa ma sicuramente ci sarà qualcosa del genere

map *dummy_map;

char n[10] = "gino";
Player *player = new Player(10, 10, NULL, NULL, n, 6, 5, {20, 15}, '@');

room a{// stanza finta
       0,
       player,
       NULL, // nessun oggetto
       NULL, // nessun mob
       {     // 2 porte (una sopra e una a destra
        new door{
            RIGHT_DOOR,
            NULL},
        new door{
            LOWER_DOOR,
            NULL},
        NULL,
        NULL}};

int main()
{
    // init schermo
    time_t inizio_frame, fine_frame;
    Screen schermo = Screen();
    // init della mappa
    dummy_map = init_map(a);
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
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
            // ...
        }
    } while (key != ERR); // finché ci sono tasti da leggere
}
