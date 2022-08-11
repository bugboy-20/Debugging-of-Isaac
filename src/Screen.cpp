#include "Screen.hpp"
#include "Events.hpp"
#include "Wall.hpp"

#include <cstring>

Screen::Screen()
{
    initscr();
    cbreak(); // ctrl+c behaviour
    noecho(); // avoids user input from being printed
    nodelay(stdscr, TRUE);
    curs_set(0);
    // setlocale(LC_ALL, ""); // dovrebbe servire per stampare caratteri speciali, ma non va. TODO documentarsi meglio
    // keypad(wroom, true);
    refresh();

    this->windows_init();
}

void Screen::render_room(Room *r)
{
    move(0, 0);

    RoomEvent *e;
    while ((e = r->get_event()) != NULL)
    {
        printw("id evento: %d ", e->id);
        switch (e->id)
        {
        case ENTITY_MOVE:
        {
            EntityMoveE *t = (EntityMoveE *)e;
            coords oldC = t->data[0], newC = t->data[1];
            char oldCh = ' ', newCh = ' ';

            Core *oldE = r->get_element_in_this_position(oldC);
            Core *newE = r->get_element_in_this_position(newC);
            if (oldE != NULL)
                oldCh = oldE->get_display();
            if (newE != NULL)
                newCh = newE->get_display();

            mvwaddch(wroom, oldC.y, oldC.x, oldCh); // vecchia posizione
            mvwaddch(wroom, newC.y, newC.x, newCh); // nuova posizione

            delete t;
            break;
        }
        case ROOM_CHANGED:
        {
            RoomChangedE *t = (RoomChangedE *)e;
            room_init(*r); // demando la logica ad una funzione esterna

            this->render_playerstat(*r); // è qui solo temporaneamente per i test
            this->render_legend(*r);
            this->render_moblist(*r);
            delete t;
            break;
        }
        case ENTITY_KILLED:
        {
            EntityKilledE *t = (EntityKilledE *)e;
            mvwaddch(wroom, t->data->get_y(), t->data->get_x(), ' ');
            this->render_moblist(*r);

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
        default:
            break;
        }
    }
    wrefresh(wroom);
}

void Screen::room_init(Room r)
{
    // pulisco lo schermo da rappresentazioni precedenti
    werase(wroom);

    // render muri esterni e delle porte
    box(wroom, 0, 0);
    print_doors(r.door);

    List everything = r.get_room_member();
    if (everything.head != NULL)
    {

        node *list = everything.head;
        // wmove(moblist, 1, 1);

        while (list != NULL)
        {
            Core *c = (Core *)list->element;
            // wprintw(moblist, "carattere:%c ", c->get_display());
            mvwaddch(wroom, c->get_y(), c->get_x(), c->get_display());
            list = list->next;
        }
        // wrefresh(moblist);
    }

    List walls = r.get_walls();
    if (walls.head != NULL)
    {
        node *list = walls.head;

        while (list != NULL)
        {
            Wall *c = (Wall *)list->element;
            coords start = {c->get_x(), c->get_y()};
            mvwaddch(wroom, start.y, start.x, c->get_display());
            if (/*c->is_wall({start.x, start.y + 1})*/ c->get_alignment()) // linea orizzontale
            {
                wmove(wroom, start.x + 1, start.y);
                wvline(wroom, c->get_display(), c->get_line_lenght() - 1);
            }
            else /*if (c->is_wall({start.x + 1, start.y}))*/ // linea verticale
            {
                wmove(wroom, start.x, start.y + 1);
                whline(wroom, c->get_display(), c->get_line_lenght() - 1);
            }
            list = list->next;
        }
    }
}

void Screen::print_doors(door *doors[])
{
    char door = ' ';

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
                // printw("%s", "sus");
                break;
            }
            mvwaddch(wroom, yLoc1, xLoc1, door);
            mvwaddch(wroom, yLoc2, xLoc2, door);
        }
    }
}

void Screen::windows_init()
{
    int lateral_width = 20,
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
    doupdate();
}

// funzione che dovrebbe essere chiamata quando:
// inizia il gioco, la vita del player aumenta o diminuisce, il player guadagna punti
void Screen::render_playerstat(Room r)
{
    // estraggo il player
    List entities = r.get_entities(true);
    if (entities.head == NULL)
        return;
    Player *player = (Player *)entities.head->element;
    if (player == NULL)
        return;

    // printw("entities: %d", player->get_health());

    wmove(playerstat, 0, 1);
    char name[10];
    player->get_name(name);
    wprintw(playerstat, "%s", name);
    wmove(playerstat, 1, 1);
    int nchars = player->get_health() / 2;
    // serve il getter per la maxHealth
    int maxHealth = player->get_max_health() / 2;
    // int maxHealth = 5; // questo è temporaneo
    for (int i = 0; i < maxHealth; i++)
    {
        if (nchars > 0)
        {
            waddch(playerstat, 'O');
            nchars--;
        }
        else
            waddch(playerstat, 'o');
    }
    wmove(playerstat, 2, 1);
    wprintw(playerstat, "%s: ", "punti"); // cosa sono i punti?

    wrefresh(playerstat);
}

// funzione che dovrebbe essere chiamata quando:
// si cambia stanza
void Screen::render_legend(Room r)
{
    mvwprintw(legend, 0, 1, "Legenda");
    int start_x = 2;
    wmove(legend, 1, start_x);

    List room_member = r.get_room_member();
    if (room_member.head != NULL)
    {
        node *list = room_member.head;
        char seenDisplay[20];
        int p = 0;

        while (list != NULL)
        {
            Core *c = (Core *)list->element;
            bool nw = true;
            char display = c->get_display();

            for (int i = 0; i < p; i++)
            {
                if (display == seenDisplay[i])
                {
                    nw = false;
                    break;
                }
            }

            if (nw)
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
    }

    wrefresh(legend);
}

// funzione che dovrebbe essere chiamata quando:
// si cambia stanza, un hostile prende danno, un hostile muore
void Screen::render_moblist(Room r)
{
    int line = 2, col = 2, gap = 4;

    wmove(moblist, line, col);
    List entities = r.get_entities(false);
    if (entities.head != NULL)
    {
        node *list = entities.head;

        while (list != NULL)
        {
            Entity *c = (Entity *)list->element;

            int start_x, start_y,
                end_x, end_y,
                end_h_x, end_h_y;

            getyx(moblist, start_y, start_x); // salvo la posizione del cursore prima di scrivere la prima riga

            char name[10];
            c->get_name(name);
            if (start_x + strlen(name) + 4 >= ROOM_WIDTH || start_x + c->get_health() >= ROOM_WIDTH) // +4 alla lunghezza del nome perchè stampo anche altri ch
            {                                                                                        // se il nome o la barra della vita non ci sta

                line += 3; // mi sposto sotto
                wmove(moblist, line, col);
            }
            else
            {
                wprintw(moblist, "%c : %s", c->get_display(), name); // stampo la prima riga
                getyx(moblist, end_y, end_x);                        // salvo la posizione del cursore dopo aver scritto la prima riga
                wmove(moblist, start_y + 1, start_x);                // mi muovo nella riga sotto

                for (int i = 0; i < c->get_health(); i++) // stampo la barra della vita
                    waddch(moblist, 'O');

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
    }
    mvwprintw(moblist, 0, 1, "Nemici");
    wrefresh(moblist);
}

void Screen::stop_screen()
{
    endwin();
}
