#pragma once
#define STR_LENGTH 20

#define Zombie_s "zombie"
// char Zombie_name[STR_LENGTH] = "Zombie";
// char Zombie_desc[STR_LENGTH] = "zombie";
#define Zombie_display 'z'
#define Zombie_health 4
#define Zombie_damage 1
#define Zombie_as 1000
#define Zombie_ms 150
#define Zombie_range 10
#define Zombie_tr 3

#define Scheletro_s "scheletro"
// char Scheletro_name[STR_LENGTH] = "Scheletro";
// char Scheletro_desc[STR_LENGTH] = "scheletro";
#define Scheletro_display 's'
#define Scheletro_health 2
#define Scheletro_damage 2
#define Scheletro_as 1000
#define Scheletro_ms 150
#define Scheletro_range 10
#define Scheletro_tr 3

#define Goblin_s "goblin"
// char Goblin_name[STR_LENGTH] = "Goblin";
// char Goblin_desc[STR_LENGTH] = "goblin";
#define Goblin_display 'g'
#define Goblin_health 1
#define Goblin_damage 4
#define Goblin_as 1000
#define Goblin_ms 150
#define Goblin_range 10
#define Goblin_tr 3

#define Fantasma_s "fantasma"
// char Fantasma_name[STR_LENGTH] = "Fantasma";
// char Fantasma_desc[STR_LENGTH] = "fantasma";
#define Fantasma_display 'f'
#define Fantasma_health 6
#define Fantasma_damage 1
#define Fantasma_as 1000
#define Fantasma_ms 150
#define Fantasma_range 10
#define Fantasma_tr 3

#define Slime_s "slime"
// char Slime_name[STR_LENGTH] = "Slime";
// char Slime_desc[STR_LENGTH] = "slime";
#define Slime_display 'l'
#define Slime_health 7
#define Slime_damage 2
#define Slime_as 1000
#define Slime_ms 150
#define Slime_range 10
#define Slime_tr 3

#define player_s "giocatore"
#define player_base_damage 3
#define player_inventory_slots 5
#define player_display '@'

#define door_display ' '
#define h_wall_display '-'
#define v_wall_display '|'

#define bullet_n "bullet"
#define bullet_d "bullet_desc"
// char bullet_name[10] = "bullet";
// char bullet_desc[20] = "bullet_desc";
#define bullet_display '.'

#define up_button 'w'
#define down_button 's'
#define left_button 'a'
#define right_button 'd'
#define quit_button 'q'

#define weapon_damage 2
#define armor_health 2
#define boots_speed 15
#define crosshair_range 15
#define booster_speed 100

#define potion_d "pozione"
#define key_d "chiave"

enum level
{
    lvl1 = 1, // BIANCO
    lvl2,     // CYAN
    lvl3,     // BLUE
    lvl4,     // GREEN
    lvl5,     // YELLOW
    lvl6,     // MAGENTA
    lvl7      // RED
};

struct stats
{
    int damage;
    int health;
    int attack_speed;
    int movement_speed;
    int range;
};
