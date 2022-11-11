#include "Screen.hpp"
#include "Events.hpp"
#include "Wall.hpp"
#include "constants.h"
#include <cstring>

Screen::Screen()
{
    initscr();
    cbreak(); // ctrl+c behaviour
    noecho(); // avoids user input from being printed
    nodelay(stdscr, TRUE);
    curs_set(0);
    // setlocale(LC_ALL, ""); // dovrebbe servire per stampare caratteri speciali, ma non va. TODO documentarsi meglio
    keypad(stdscr, true);
    refresh();

    this->windows_init();
}

void Screen::do_screen(Room *r)
{
    wmove(debug, 0, 0);

    RoomEvent *e;
    while ((e = r->get_event()) != NULL)
    {
        wprintw(debug, "id evento: %d \n", e->id);
        switch (e->id)
        {
        case ENTITY_MOVE:
        {
            EntityMoveE *t = (EntityMoveE *)e;
            coords oldC = t->data[0], newC = t->data[1];
            char oldCh = ' ', newCh = t->ed;

            Core *oldE = r->get_element_in_this_position(oldC);
            if (oldE != NULL)
                oldCh = oldE->get_display();

            mvwaddch(wroom, oldC.y, oldC.x, oldCh); // vecchia posizione
            mvwaddch(wroom, newC.y, newC.x, newCh); // nuova posizione
            wrefresh(wroom);

            delete t;
            break;
        }
        case ROOM_CHANGED:
        {
            RoomChangedE *t = (RoomChangedE *)e;

            this->render_room(*r);       // stampo la stanza per la prima volta
            this->render_playerstat(*r); // è qui solo temporaneamente per i test
            this->render_legend(*r);
            this->render_moblist(*r);
            this->render_inventory(*r);

            delete t;
            break;
        }
        case ENTITY_KILLED:
        {
            EntityKilledE *t = (EntityKilledE *)e;

            char ch = ' ';
            Core *el = r->get_element_in_this_position({t->data->get_x(), t->data->get_y()});

            if (el != NULL)
                ch = el->get_display();

            mvwaddch(wroom, t->data->get_y(), t->data->get_x(), ch);
            wnoutrefresh(wroom);
            this->render_moblist(*r);

            t->destroy();
            delete t;
            break;
        }
        case ENTITY_DAMAGED:
        {
            EntityDamagedE *t = (EntityDamagedE *)e;

            this->render_moblist(*r);

            delete t;
            break;
        }
        case PLAYER_HEALTH_CHANGED:
        {
            PlayerHealthChangedE *t = (PlayerHealthChangedE *)e;

            this->render_playerstat(*r);

            delete t;
            break;
        }
        case CONSUMABLE_USED:
        {
            ConsumableUsedE *t = (ConsumableUsedE *)e;

            this->render_inventory(*r);

            delete t;
            break;
        }
        default:
            break;
        }
    }
    wrefresh(debug);
}

void Screen::stop_screen()
{
    delwin(wroom);
    delwin(playerstat);
    delwin(legend);
    delwin(moblist);
    delwin(inventory);
    endwin();
}

void Screen::windows_init()
{
    lateral_width = 20,
    lower_height = 10,
    playerstat_height = 4,
    legend_height = (ROOM_HEIGHT + lower_height - playerstat_height) / 2,
    inventory_height = ROOM_HEIGHT + lower_height - playerstat_height - legend_height,
    moblist_width = ROOM_WIDTH,
    start_x = 1,
    start_y = 0,
    lateral_start_x = ROOM_WIDTH + 1 + start_x,
    lower_start_y = ROOM_HEIGHT;

    wroom = newwin(ROOM_HEIGHT, ROOM_WIDTH, start_y, start_x);
    playerstat = newwin(playerstat_height, lateral_width, start_y, lateral_start_x);
    legend = newwin(legend_height, lateral_width, playerstat_height + start_y, lateral_start_x);
    inventory = newwin(inventory_height, lateral_width, playerstat_height + legend_height + start_y, lateral_start_x);
    moblist = newwin(lower_height, moblist_width, lower_start_y + start_y, start_x);
    debug = newwin(50, 30, start_y, lateral_start_x + lateral_width + 3);
    box(wroom, 0, 0);
    box(playerstat, 0, 0);
    box(legend, 0, 0);
    box(inventory, 0, 0);
    box(moblist, 0, 0);

    // refresh();
    wnoutrefresh(wroom);
    wnoutrefresh(playerstat);
    wnoutrefresh(legend);
    wnoutrefresh(inventory);
    wnoutrefresh(moblist);
    wnoutrefresh(debug);
    doupdate();
}

void Screen::print_doors(door *doors[])
{
    char door = door_display;

    for (int i = 0; i < 4; i++)
    {
        if (doors[i] != NULL)
        {
            int yLoc1, xLoc1, yLoc2, xLoc2;

            switch ((*doors[i]).position)
            {
            case UPPER_DOOR:
                yLoc1 = yLoc2 = 0;
                xLoc1 = (ROOM_WIDTH / 2) - 1;
                xLoc2 = (ROOM_WIDTH / 2);
                break;
            case LOWER_DOOR:
                yLoc1 = yLoc2 = ROOM_HEIGHT - 1;
                xLoc1 = (ROOM_WIDTH / 2) - 1;
                xLoc2 = (ROOM_WIDTH / 2);
                break;
            case RIGHT_DOOR:
                yLoc1 = (ROOM_HEIGHT / 2) - 1;
                yLoc2 = (ROOM_HEIGHT / 2);
                xLoc1 = xLoc2 = ROOM_WIDTH - 1;
                break;
            case LEFT_DOOR:
                yLoc1 = (ROOM_HEIGHT / 2) - 1;
                yLoc2 = (ROOM_HEIGHT / 2);
                xLoc1 = xLoc2 = 0;
                break;

            default:
                break;
            }
            mvwaddch(wroom, yLoc1, xLoc1, door);
            mvwaddch(wroom, yLoc2, xLoc2, door);
        }
    }
}

void Screen::render_room(Room &r)
{
    // pulisco lo schermo da rappresentazioni precedenti
    werase(wroom);

    // render muri esterni e delle porte
    box(wroom, 0, 0);
    print_doors(r.door);

    // render degli elementi (dei muri solo la "testa")
    List everything = r.get_room_member(false);
    node *list = everything.head;

    while (list != NULL)
    {
        Core *c = (Core *)list->element;
        if (c->get_x() < ROOM_WIDTH - 1 && c->get_y() < ROOM_HEIGHT - 1)
            mvwaddch(wroom, c->get_y(), c->get_x(), c->get_display());
        list = list->next;
    }

    // stampo i muri per intero, procedimento diverso dagli altri elementi perchè sono più caratteri
    List walls = r.get_walls();
    list = walls.head;

    while (list != NULL)
    {
        Wall *c = (Wall *)list->element;
        if (c->get_x() < ROOM_WIDTH - 1 && c->get_y() < ROOM_HEIGHT - 1)
        {
            wmove(wroom, c->get_y(), c->get_x());

            if (c->get_alignment())                                        // linea verticale
                wvline(wroom, c->get_display(), c->get_line_lenght() + 1); // stampo la testa + il corpo
            else                                                           // linea orizzontale
                whline(wroom, c->get_display(), c->get_line_lenght() + 1);
        }
        list = list->next;
    }
    wrefresh(wroom);
}

void Screen::render_playerstat(Room &r)
{
    // estraggo il player
    Player *player = (Player *)r.p;
    if (player == NULL)
        return;

    int start_x = 1;
    char fullHeart = '0', // cuore intero
        halfHeart = 'O',  // mezzo cuore
        emptyHeart = '-'; // cuore vuoto

    int nFullHeart = player->get_health() / 2,
        nHalfHeart = player->get_health() - nFullHeart * 2,                           // get_health è dispari allora è 1 se è pari è 0
        nEmptyHeart = ((player->get_max_health() + 1) / 2) - nFullHeart - nHalfHeart; // tutto ciò che non è cuori pieni o mezzi, sono cuori vuoti

    // stampo il nome
    char name[10];
    player->get_name(name);
    mvwprintw(playerstat, 0, start_x, "%s", name);

    // stampo la vita
    wmove(playerstat, 1, start_x);

    for (int i = 0; i < nFullHeart; i++)
        waddch(playerstat, fullHeart);

    for (int i = 0; i < nHalfHeart; i++)
        waddch(playerstat, halfHeart);

    for (int i = 0; i < nEmptyHeart; i++)
        waddch(playerstat, emptyHeart);

    // stampo i punti
    mvwprintw(playerstat, 2, start_x, "%s: %d", "punti", player->get_score());

    wrefresh(playerstat);
}

void Screen::render_legend(Room &r)
{
    werase(legend);
    box(legend, 0, 0);

    mvwprintw(legend, 0, 1, "Legenda");
    int start_x = 2;
    wmove(legend, 1, start_x);

    List room_member = r.get_room_member(true);
    node *list = room_member.head;

    char seenDisplay[20];
    int p = 0;

    while (list != NULL)
    {
        Core *c = (Core *)list->element;
        bool nw = true;
        char display = c->get_display();

        for (int i = 0; i < p; i++) // controllo se questo carattere è già stato inserito nella legenda
        {
            if (display == seenDisplay[i])
            {
                nw = false;
                break; // appena ne trovo uno uguale non lo devo stampare e posso smettere di cercare
            }
        }

        if (nw) // se non è stato inserito lo faccio qui
        {
            seenDisplay[p++] = display;
            int x, y;
            getyx(legend, y, x);
            wmove(legend, y + 1, start_x);

            char desc[20];
            c->get_description(desc);
            wprintw(legend, "%c : %s", display, desc);
        }

        list = list->next;
    }

    wrefresh(legend);
}

void Screen::render_moblist(Room &r)
{
    werase(moblist);
    box(moblist, 0, 0);

    int line = 2, col = 2, gap = 4;
    char fullHeart = '0', // cuore intero
        halfHeart = 'O';  // mezzo cuore

    wmove(moblist, line, col);
    List entities = r.get_entities(false);
    node *list = entities.head;

    while (list != NULL)
    {
        Entity *c = (Entity *)list->element;

        int start_x, start_y,
            end_x, end_y,
            end_h_x, end_h_y;

        int nFullHeart = c->get_health() / 2,
            nHalfHeart = c->get_health() - nFullHeart * 2; // get_health è dispari allora è 1 se è pari è 0

        getyx(moblist, start_y, start_x); // salvo la posizione del cursore prima di scrivere la prima riga

        char name[10];
        c->get_name(name);
        if (start_x + strlen(name) + 4 >= ROOM_WIDTH || start_x + nFullHeart + nHalfHeart >= ROOM_WIDTH) // +4 alla lunghezza del nome perchè stampo anche altri ch
        {                                                                                                // se il nome o la barra della vita non ci sta

            line += 3; // mi sposto sotto
            wmove(moblist, line, col);
        }
        else
        {
            wprintw(moblist, "%c : %s", c->get_display(), name); // stampo la prima riga
            getyx(moblist, end_y, end_x);                        // salvo la posizione del cursore dopo aver scritto la prima riga
            wmove(moblist, start_y + 1, start_x);                // mi muovo nella riga sotto

            for (int i = 0; i < nFullHeart; i++) // stampo la barra della vita
                waddch(moblist, fullHeart);
            for (int i = 0; i < nHalfHeart; i++)
                waddch(moblist, halfHeart);

            getyx(moblist, end_h_y, end_h_x);

            if (end_h_x + gap >= ROOM_WIDTH || end_x + gap >= ROOM_WIDTH) // se una delle due coordinate sfora si cambia riga
            {
                line += 3;
                wmove(moblist, line, col);
            }
            else // altrimenti la nuova posizione sarà la più grande delle due
            {
                if (end_x > end_h_x)
                    wmove(moblist, end_y, end_x + gap);
                else
                    wmove(moblist, end_y, end_h_x + gap);
            }

            list = list->next;
        }
    }
    mvwprintw(moblist, 0, 1, "Nemici");
    wrefresh(moblist);
}

void Screen::render_inventory(Room &r)
{
    werase(inventory);
    box(inventory, 0, 0);
    // stampare gli slot dell'inventario, che sono player_inventory_slots
    int start_x = 2, curr_x = start_x, start_y = 4, curr_y = start_y, spacing = 2;
    mvwprintw(inventory, 2, start_x, "%c:%d    %c:%d",
              r.p->get_inventory().pots.display,
              r.p->get_inventory().pots.get_n_utilizzi(),
              r.p->get_inventory().keys.display,
              r.p->get_inventory().keys.get_n_utilizzi());

    for (int i = 0; i < player_inventory_slots; i++)
    {
        char d = '.';
        if (r.p->get_inventory().items[i] != NULL)
            d = r.p->get_inventory().items[i]->display;

        wmove(inventory, start_y, curr_x);
        waddch(inventory, d);
        if (curr_x + spacing + 2 >= lateral_width) //+2 uno è il bordo e l'altro è per il padding
        {
            start_y += spacing - 1;
            curr_x = start_x - spacing;
        }

        curr_x += spacing;
    }

    Weapon *w = r.p->get_inventory().arma;
    Armor *a = r.p->get_inventory().armatura;
    getyx(inventory, curr_y, curr_x);
    if (w != NULL)
        mvwprintw(inventory, curr_y + 2, 2, "%c", w->display);
    if (a != NULL)
        mvwprintw(inventory, curr_y + 2, 4, "%c", a->display);
    mvwprintw(inventory, 0, 1, "Inventario");
    wrefresh(inventory);
}
