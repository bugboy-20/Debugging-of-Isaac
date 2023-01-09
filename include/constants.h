#pragma once
#define STR_LENGTH 20

#define MAX_SMARTNESS 10

#define Zombie_s "zombie"
#define Zombie_display 'z'
#define Zombie_damage 1
#define Zombie_health 4
#define Zombie_as 1500
#define Zombie_ms 280
#define Zombie_range 6
#define Zombie_tr 5
#define Zombie_smartness 0
#define Zombie_ds 1
#define Zombie_hs 2

#define Scheletro_s "scheletro"
#define Scheletro_display 's'
#define Scheletro_damage 2
#define Scheletro_health 2
#define Scheletro_as 1000
#define Scheletro_ms 280
#define Scheletro_range 15
#define Scheletro_tr 13
#define Scheletro_smartness 0
#define Scheletro_ds 1
#define Scheletro_hs 2

#define Goblin_s "goblin"
#define Goblin_display 'g'
#define Goblin_health 3
#define Goblin_damage 3
#define Goblin_as 1500
#define Goblin_ms 230
#define Goblin_range 4
#define Goblin_tr 3
#define Goblin_smartness 0
#define Goblin_ds 3
#define Goblin_hs 1

#define Fantasma_s "fantasma"
#define Fantasma_display 'f'
#define Fantasma_damage 2
#define Fantasma_health 2
#define Fantasma_as 1500
#define Fantasma_ms 260
#define Fantasma_range 6
#define Fantasma_tr 5
#define Fantasma_smartness 5
#define Fantasma_ds 1
#define Fantasma_hs 1

#define Ragno_s "ragno"
#define Ragno_display 'r'
#define Ragno_damage 1
#define Ragno_health 2
#define Ragno_as 800
#define Ragno_ms 250
#define Ragno_range 4
#define Ragno_tr 3
#define Ragno_smartness 0
#define Ragno_ds 2
#define Ragno_hs 1

#define Mummia_s "mummia"
#define Mummia_display 'm'
#define Mummia_damage 2
#define Mummia_health 5
#define Mummia_as 2000
#define Mummia_ms 330
#define Mummia_range 6
#define Mummia_tr 5
#define Mummia_smartness 7
#define Mummia_ds 1
#define Mummia_hs 3

#define Torretta_s "torretta"
#define Torretta_display 't'
#define Torretta_damage 3
#define Torretta_health 2
#define Torretta_as 1000
#define Torretta_ms 5000
#define Torretta_range 500
#define Torretta_tr 499
#define Torretta_smartness MAX_SMARTNESS
#define Torretta_ds 2
#define Torretta_hs 2

#define Golem_s "Golem BOSS"
#define Golem_display 'G'
#define Golem_damage 10
#define Golem_health 35
#define Golem_as 2200
#define Golem_ms 500
#define Golem_range 9
#define Golem_tr 8
#define Golem_smartness 4
#define Golem_ds 0
#define Golem_hs 0

#define Mago_s "Mago BOSS"
#define Mago_display 'M'
#define Mago_damage 20
#define Mago_health 28
#define Mago_as 1700
#define Mago_ms 200
#define Mago_range 30
#define Mago_tr 29
#define Mago_smartness 5
#define Mago_ds 0
#define Mago_hs 0

#define Drago_s "Drago BOSS"
#define Drago_display 'D'
#define Drago_damage 13
#define Drago_health 30
#define Drago_as 2000
#define Drago_ms 200
#define Drago_range 15
#define Drago_tr 14
#define Drago_smartness 5
#define Drago_ds 0
#define Drago_hs 0

#define player_s "giocatore"
#define player_inventory_slots 5
#define player_display '@'
#define player_damage 3
#define player_health 14
#define player_as 1000
#define player_ms 150
#define player_range 9

#define open_door_display ' '
#define locked_door_display '+'
#define h_wall_display '-'
#define v_wall_display '|'

#define bullet_d "bullet_desc"
#define bullet_display '.'

#define up_button 'w'
#define down_button 's'
#define left_button 'a'
#define right_button 'd'
#define quit_button 'q'
#define heal_button 'h'
#define new_game_button 'n'

#define weapon_damage 2
#define armor_health 2
#define boots_speed 2
#define crosshair_range 15
#define booster_speed 2

#define potion_d "pozione"
#define potion_display '+'
#define key_d "chiave"
#define key_display 'k'

#define key_spawn_rate 20
#define pot_spwan_rate 20

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
    double attack_speed;
    double movement_speed;
    int range;
};
