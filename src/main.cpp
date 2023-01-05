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
#include "ItemOnGround.hpp"
#include "Events.hpp"

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
// #define sleep_time(ti,tf) (FRAMETIME - (tf - ti))
int sleep_time(timeval start, timeval end);
void controller(Player *); // gestisce la tastiera

void exit_game(); // permette di uscire
void reset_game(); // reset del game

// true se deve essere eseguito un altro menù
bool menu(Screen &); // apre il menu
void game_loop();
void controls(Screen &); // apre l'interfaccia dei controlli

map *dummy_map;

char desc5[20] = "sasso";
char desc1[20] = "spada";

Zombie *z = new Zombie({45, 15});
Ragno *ragno = new Ragno({40, 15});
Scheletro *scheleton = new Scheletro({60, 7});
Goblin *goblin = new Goblin({20, 10});
Fantasma *fantasma = new Fantasma({22, 4});
Core *rock = new Core({35, 7}, 'O', desc5);
Wall *w1 = new Wall({{ROOM_WIDTH / 2, ROOM_HEIGHT / 4}, false, ROOM_WIDTH / 4});
Wall *w2 = new Wall({{10, 7}, true, ROOM_HEIGHT / 4});
Weapon *spada = new Weapon(item, '\\', desc1, lvl5);
ItemOnGround *s = new ItemOnGround({5, 5}, spada);

Player *player;

Screen schermo;
int main()
{
    int key;
    do
    {
        // init schermo e player
        schermo = Screen();
        player = new Player({20, 15});

        // apro il menu
        bool again;
        do
        {
            again = menu(schermo);
        } while (again);

        // init della mappa
        dummy_map = init_map(player,1);
        player->add_item(spada);

        // aggiungo elementi alla stanza
        dummy_map->current_room->add_entity(ragno);
        dummy_map->current_room->add_entity(scheleton);
        dummy_map->current_room->add_entity(goblin);
        dummy_map->current_room->add_entity(fantasma);
        dummy_map->current_room->add_entity(z);
        dummy_map->current_room->add_Core(rock);
        dummy_map->current_room->add_items_on_ground(s);
        dummy_map->current_room->add_wall(w2);
        // dummy_map->current_room->add_wall(w1);

        game_loop();
        key = schermo.print_game_over();
        destroy_map(*dummy_map);
        *dummy_map = {NULL,NULL};
        delete player;
        schermo.stop_screen();

    } while (key != quit_button);
    exit_game();
}

bool menu(Screen &schermo)
{
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
        else if (key == KEY_DOWN || key == 's')
            schermo.gm.select_next_item();
        else if (key == KEY_UP || key == 'w')
            schermo.gm.select_prev_item();
    } while (true);
    schermo.gm.clean();

    bool again = false;
    switch (selected_menu)
    {
    case NEW_GAME:
        // game loop
        break;

    case CONTROLS:
        controls(schermo);
        again = true;
        break;

    case EXIT_GAME:
        exit_game();
        break;

    default:
        exit_game(); // qualcosa è andato storto meglio uscire
        break;
    }
    return again;
}

void controls(Screen &schermo)
{
    schermo.start_gamecontrols();
    int key = '0'; // random key giusto per farlo entrare nel ciclo la prima volta
    while (getch() != 'q')
        ;
    schermo.gc.clean();
}

void game_loop()
{
    timeval inizio_frame, fine_frame;

    schermo.start_gameinterface(dummy_map->current_room);
    while (!game_over(*player))
    {
        // il secondo parametro è la timezone, non importa usare quella giusta basta che sia uguale ovunque
        time_now(inizio_frame);

        controller(player);

        do_room(dummy_map->current_room);
        schermo.gi.set_room(dummy_map->current_room);
        schermo.gi.handle_events();

        time_now(fine_frame);
#ifdef _WIN32
        Sleep(sleep_time(inizio_frame, fine_frame));
#else
        usleep(utom(sleep_time(inizio_frame, fine_frame))); // usleep specifica quanti micro secondi sospendere l'esecuzione
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
        if (key - '0' >= 1 && key - '0' <= player_inventory_slots)
        {
            int slot = key - '0' - 1;
            if (player->get_inventory().items[slot] != NULL)
            {
                drop_item(*dummy_map->current_room, slot);
            }
            continue;
        }
        switch (key)
        {
        case up_button:
            player->move_up(dummy_map->current_room);
            break;
        case left_button:
            player->move_left(dummy_map->current_room);
            break;
        case right_button:
            player->move_right(dummy_map->current_room);
            break;
        case down_button:
            player->move_down(dummy_map->current_room);
            break;
        case quit_button:
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
        case heal_button:
            player->use_potion(dummy_map->current_room);
            break;
        case 'p': // tasto suicidio
            player->set_health(0);
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

int sleep_time(timeval start, timeval end)
{
    time_t te = time_elapsed(start, end);
    if (te > FRAMETIME)
        return 0;
    return FRAMETIME - te;
}
