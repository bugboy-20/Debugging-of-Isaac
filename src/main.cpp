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
#include "HostileList.hpp"
#include "GameMenu.hpp"
#include <locale.h>

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

void menu(Screen&); //apre il menu
void game_loop();

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

Zombie *z = new Zombie({45, 15});

Hostile *villan = new Hostile(3, n1, 8, 5, {40, 15}, '*', desc1);
Hostile *villan1 = new Hostile(3, n2, 3, 5, {60, 7}, '=', desc2);
Hostile *villan2 = new Hostile(3, n3, 7, 5, {20, 10}, '$', desc3);
Hostile *villan3 = new Hostile(3, n4, 10, 5, {22, 4}, ')', desc4);
Core *rock = new Core({35, 7}, 'O', desc5);
Wall *w1 = new Wall({{ROOM_WIDTH / 2, ROOM_HEIGHT / 4}, false, ROOM_WIDTH / 4});
Wall *w2 = new Wall({{10, 7}, true, ROOM_HEIGHT / 4});

Player *player = new Player(10, 10, NULL, NULL, n, 6, 5, {20, 15}, '@', desc);

Screen schermo;
int main()
{

    setlocale(LC_ALL, "");
    //^^^^^^^^^^^^^^^^^^^^^^^ piske che fa Ctrl+C Ctrl+V alla cieca


    // init schermo
    schermo = Screen();

    // apro il menu
    menu(schermo);

    // init della mappa
    dummy_map = init_map(player);

    schermo.start_gameinterface();

    // aggiungo elementi alla stanza
    dummy_map->current_room->add_entity(villan);
    dummy_map->current_room->add_entity(villan1);
    dummy_map->current_room->add_entity(villan2);
    dummy_map->current_room->add_entity(villan3);
    dummy_map->current_room->add_entity(z);
    dummy_map->current_room->add_Core(rock);
    dummy_map->current_room->add_wall(w2);
    // dummy_map->current_room->add_wall(w1);

    game_loop();
}

void menu(Screen& schermo) {
    schermo.start_gamemenu();
    int selected_menu, key;

    // loop di controllo del menù
    do
    {
        schermo.gm.draw();
        key = getch();
        if (key == '\n')
        {
            selected_menu = schermo.gm.get_selected_item();
            break;
        }
        else if (key == KEY_UP || key == 'w')
            schermo.gm.select_next_item();
        else if (key == KEY_DOWN || key == 's')
            schermo.gm.select_prev_item();
    } while (true);
    schermo.gm.clean();

    switch (selected_menu)
    {
        case NEW_GAME:
            // game loop
            break;

        case EXIT_GAME:
            exit_game();
            break;

        default:
            exit_game(); // qualcosa è andato storto meglio uscire
            break;
    }
}

void game_loop() {
    time_t inizio_frame, fine_frame;
    while (!game_over(*player))
    {
        inizio_frame = time(0);

        controller(player);

        //do_room(dummy_map->current_room);
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
