#include "Screen.hpp"
#include "List.hpp"
#include "Events.hpp"

Screen::Screen()
{
    initscr();
    cbreak(); // ctrl+c behaviour
    noecho(); // avoids user input from being printed
    nodelay(stdscr, TRUE);
    curs_set(0);
    // keypad(wroom, true);
    refresh();

    this->windows_init();
    x = true;
}

void Screen::render_room(Room r)
{

    if (this->x)
    {
        this->render_playerstat(r);
        this->room_init(r);
        x = false;
    }

    RoomEvent *e;
    while ((e = r.get_event()) != NULL)
    {
        printw("%s", "ziocaca");
        switch (e->id)
        {
        case ENTITY_MOVE:
        {
            EntityMoveE *t = (EntityMoveE *)e;
            coords oldC = t->data[0];
            coords newC = t->data[1];
            Core *e = r.get_element_in_this_position(oldC);
            mvwaddch(wroom, oldC.y, newC.x, ' ');
            mvwaddch(wroom, oldC.y, newC.x, e->getDisplay());
            delete t;
            break;
        }
        case ROOM_CHANGED:
        {
            RoomChangedE *t = (RoomChangedE *)e;
            room_init(r); // demando la logica ad una funzione esterna
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
    if (everything.head == NULL)
        return;

    node *list = everything.head;

    while (list != NULL)
    {
        Core *c = (Core *)list->element;
        mvwaddch(wroom, c->getY(), c->getX(), c->getDisplay());
        list = list->next;
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

void Screen::render_playerstat(Room r)
{
    wmove(playerstat, 1, 1);
    node *t = r.get_entities(true).head;
    Core *player;
    if (t != NULL)
        player = (Core *)t->element;
    printw("entities: %c", player->getDisplay());
    // wprintw(playerstat, "%c: ", player->getDisplay());
    // int nchars = player->getX() / 2;
    // for (int i = 0; i < 5; i++)
    // {
    //     if (nchars > 0)
    //     {
    //         waddch(playerstat, 'O');
    //         nchars--;
    //     }
    //     else
    //         waddch(playerstat, 'o');
    // }
    // wmove(playerstat, 2, 1);
    // wprintw(playerstat, "%s: ", "punti");

    // refresh();
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
    // wmove(legend, 1, 1);
    // while (r.items != NULL)
    // {

    //     r.items = r.items->next;
    // }

    // // render entità
    // while (r.entities != NULL)
    // {
    //     r.entities = r.entities->next;
    // }
}

void Screen::stop_screen()
{
    endwin();
}