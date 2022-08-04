#include "Screen.hpp"
#include "List.hpp"
#include "Events.hpp"
#include "Wall.hpp"

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
    x = true;
}

void Screen::render_room(Room *r)
{
    move(0, 0);

    // if (this->x)
    // {
    //     this->render_playerstat(r);
    //     // this->room_init(r);
    //     x = false;
    // }

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
                oldCh = oldE->getDisplay();
            if (newE != NULL)
                newCh = newE->getDisplay();

            mvwaddch(wroom, oldC.y, oldC.x, oldCh); // vecchia posizione
            mvwaddch(wroom, newC.y, newC.x, newCh); // nuova posizione

            delete t;
            break;
        }
        case ROOM_CHANGED:
        {
            RoomChangedE *t = (RoomChangedE *)e;
            room_init(*r); // demando la logica ad una funzione esterna
            this->render_playerstat(*r);
            this->render_legend(*r);
            delete t;
            break;
        }
        case ENTITY_KILLED:
        {
            EntityKilledE *t = (EntityKilledE *)e;
            mvwaddch(wroom, t->data->getY(), t->data->getX(), ' ');
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
            // wprintw(moblist, "carattere:%c ", c->getDisplay());
            mvwaddch(wroom, c->getY(), c->getX(), c->getDisplay());
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
            coords start = {c->getX(), c->getY()};
            mvwaddch(wroom, start.y, start.x, c->getDisplay());
            if (/*c->is_wall({start.x, start.y + 1})*/ c->get_alignment()) // linea orizzontale
            {
                wmove(wroom, start.x + 1, start.y);
                wvline(wroom, c->getDisplay(), c->get_line_lenght() - 1);
            }
            else /*if (c->is_wall({start.x + 1, start.y}))*/ // linea verticale
            {
                wmove(wroom, start.x, start.y + 1);
                whline(wroom, c->getDisplay(), c->get_line_lenght() - 1);
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

// funzione che dovrebbe essere chiamata quando:
// inizia il gioco, il player prende danno, il player guadagna punti
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
    wprintw(playerstat, "%s", player->get_name());
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

void Screen::render_legend(Room r)
{
    int start_x = 2;
    wmove(legend, 1, start_x);
    List entities = r.get_entities(true);
    if (entities.head != NULL)
    {
        Player *player = (Player *)entities.head->element;
        if (player != NULL)
            wprintw(legend, "%c : %s", player->getDisplay(), "player");

        node *list = entities.head->next;

        while (list != NULL)
        {
            Entity *c = (Entity *)list->element;
            int x, y;
            getyx(legend, y, x);
            wmove(legend, y + 1, start_x);

            wprintw(legend, "%c : %s", c->getDisplay(), "entity");

            list = list->next;
        }
    }

    List walls = r.get_walls();
    if (walls.head != NULL)
    {
        node *list = walls.head;

        while (list != NULL)
        {
            Wall *c = (Wall *)list->element;
            int x, y;
            getyx(legend, y, x);
            wmove(legend, y + 1, start_x);

            wprintw(legend, "%c : %s", c->getDisplay(), "wall");

            list = list->next;
        }
    }

    wrefresh(legend);
}

void Screen::stop_screen()
{
    endwin();
}
