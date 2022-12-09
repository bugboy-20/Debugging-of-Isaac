#include "GameInterface.hpp"

#include "Events.hpp"
#include "Wall.hpp"
#include <cstring>

GameInterface::GameInterface(WINDOW *wroom, WINDOW *pstat, WINDOW *legend, WINDOW *moblist, WINDOW *inv)
{
    this->wroom = wroom;
    this->playerstat = pstat;
    this->legend = legend;
    this->moblist = moblist;
    this->inventory = inv;
    newEvents = true;
    debug = newwin(50, 30, 0, 130);
    wrefresh(debug);
}

void GameInterface::set_room(Room *r) { this->r = r; }

void GameInterface::handle_events()
{
    // wmove(debug, 0, 0);
    RoomEvent *e;
    while ((e = r->get_event()) != NULL)
    {
        if (newEvents)
        {
            newEvents = false;
            // werase(debug);
        }
        // wprintw(debug, "id evento: %d \n", e->id);
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

            this->render_room();       // stampo la stanza per la prima volta
            this->render_playerstat(); // è qui solo temporaneamente per i test
            this->render_legend();
            this->render_moblist();
            this->render_inventory();

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
            this->render_moblist();

            t->destroy();
            delete t;
            break;
        }
        case ENTITY_DAMAGED:
        {
            EntityDamagedE *t = (EntityDamagedE *)e;

            this->render_moblist();

            delete t;
            break;
        }
        case PLAYER_HEALTH_CHANGED:
        {
            PlayerHealthChangedE *t = (PlayerHealthChangedE *)e;

            this->render_playerstat();

            delete t;
            break;
        }
        case INVENTORY_CHANGED:
        {
            InventoryChangedE *t = (InventoryChangedE *)e;

            this->render_inventory();

            delete t;
            break;
        }
        case ITEM_PICKED:
        {
            ItemPickedE *t = (ItemPickedE *)e;

            char ch = ' ';
            Core *el = r->get_element_in_this_position({t->data->get_x(), t->data->get_y()});

            if (el != NULL)
                ch = el->get_display();

            mvwaddch(wroom, t->data->get_y(), t->data->get_x(), ch);
            wnoutrefresh(wroom);
            this->render_inventory();
            this->render_playerstat();

            t->destroy();
            delete t;
            break;
        }
        default:
            break;
        }
    }
    // wrefresh(debug);
    newEvents = true;
}

void GameInterface::print_doors(door *doors[])
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
                break;
            }
            mvwaddch(wroom, yLoc1, xLoc1, door);
            mvwaddch(wroom, yLoc2, xLoc2, door);
        }
    }
}

void GameInterface::render_room()
{
    // pulisco lo schermo da rappresentazioni precedenti
    werase(wroom);

    // render muri esterni e delle porte
    box(wroom, 0, 0);
    print_doors(r->door);

    // render degli elementi (dei muri solo la "testa")
    List everything = r->get_room_member(false);
    node *list = everything.head;

    while (list != NULL)
    {
        Core *c = (Core *)list->element;
        if (c->get_x() < ROOM_WIDTH - 1 && c->get_y() < ROOM_HEIGHT - 1)
            mvwaddch(wroom, c->get_y(), c->get_x(), c->get_display());
        list = list->next;
    }

    // stampo i muri per intero, procedimento diverso dagli altri elementi perchè sono più caratteri
    List walls = r->get_walls();
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

void GameInterface::render_playerstat()
{
    // estraggo il player
    Player *player = (Player *)r->p;
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

void GameInterface::render_legend()
{
    werase(legend);
    box(legend, 0, 0);

    mvwprintw(legend, 0, 1, "Legenda");
    int start_x = 2;
    wmove(legend, 1, start_x);

    List room_member = r->get_room_member(true);
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

void GameInterface::render_moblist()
{
    werase(moblist);
    box(moblist, 0, 0);

    int line = 2, col = 2, gap = 4;
    char fullHeart = '0', // cuore intero
        halfHeart = 'O';  // mezzo cuore

    wmove(moblist, line, col);
    List entities = r->get_entities(false);
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

void GameInterface::render_inventory()
{
    werase(inventory);
    box(inventory, 0, 0);
    // stampare gli slot dell'inventario, che sono player_inventory_slots
    int start_x = 2, curr_x = start_x, start_y = 2, curr_y = start_y, spacing = 2;
    struct inventory p_inv = r->p->get_inventory();
    Potion p = r->p->get_inventory().pots;
    Key k = r->p->get_inventory().keys;

    // stampo il simbolo delle pozioni colorato
    wattron(inventory, COLOR_PAIR(p.get_level()));
    mvwaddch(inventory, start_y, start_x, p.get_display());
    wattroff(inventory, COLOR_PAIR(p.get_level()));

    // stampo il resto della riga
    wprintw(inventory, ":%d    %c:%d", p.get_n_utilizzi(), k.get_display(), k.get_n_utilizzi());

    start_y += 2;
    // stampa l'inventario
    for (int i = 0; i < player_inventory_slots; i++)
    {
        Item *curr = r->p->get_inventory().items[i];
        if (curr != NULL)
        {
            wattron(inventory, COLOR_PAIR(curr->get_level()));
            mvwaddch(inventory, start_y, curr_x, curr->get_display());
            wattroff(inventory, COLOR_PAIR(curr->get_level()));
        }
        else
            mvwaddch(inventory, start_y, curr_x, '_');
        // TODO: 20 sarebbe la lateral_width
        if (curr_x + spacing + 2 >= 20) //+2 uno è il bordo e l'altro è per il padding
        {
            start_y += spacing - 1;
            curr_x = start_x - spacing;
        }

        curr_x += spacing;
    }

    getyx(inventory, curr_y, curr_x);
    curr_y += 3;
    mvwprintw(inventory, curr_y, start_x, "%s: %d", "damage", r->p->get_damage());
    curr_y += 1;
    mvwprintw(inventory, curr_y, start_x, "%s: %d", "health", r->p->get_max_health());
    curr_y += 1;
    mvwprintw(inventory, curr_y, start_x, "%s: %d", "as", 1000 / r->p->get_attack_speed());
    curr_y += 1;
    mvwprintw(inventory, curr_y, start_x, "%s: %d", "ms", 1000 / r->p->get_movement_speed());
    curr_y += 1;
    mvwprintw(inventory, curr_y, start_x, "%s: %d", "range", r->p->get_range());

    mvwprintw(inventory, 0, 1, "Inventario");
    wrefresh(inventory);
}
