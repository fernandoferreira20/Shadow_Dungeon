/**
 * @file game_engine.c
 * @author Harshit 908571
 * @brief Initialize a new game state
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <stdbool.h>
 #include "game_engine.h"
 #include "../include/game_types.h"
 #include "../menus/main_menu.h"

 void initialize_data(GameData *data){
    if(data == NULL) return;

    //used to reset our hero's stats
    data->current_hero.life_points = 20;
    data->current_hero.coins = 0;
    data->current_hero.potions_count = 0;

    //used to reset the inventory
    data->current_hero.has_armor = false;
    data->current_hero.has_sword = false;
    data->current_hero.has_hero_sword = false;
    data->current_hero.has_hero = false;

    //reset missions
    data->missions[0].type = MISSION_SWAMP;
    data->missions[0].is_completed = false;
    data->missions[0].progress_counter = 0;
    data->missions[0].key_recovered = false;
    data->missions[0].sword_recovered = false;

    data->missions[1].type = MISSION_MANSION;
    data->missions[1].is_completed = false;
    data->missions[1].progress_counter = 0;
    data->missions[1].key_recovered = false;
    data->missions[1].sword_recovered = false;

    data->missions[2].type = MISSION_CAVE;
    data->missions[2].is_completed = false;
    data->missions[2].progress_counter = 0;
    data->missions[2].key_recovered = false;
    data->missions[2].sword_recovered = false;

    data->missions[3].type = MISSION_CASTLE;
    data->missions[3].is_completed = false;
    data->missions[3].progress_counter = 0;
    data->missions[3].key_recovered = false;
    data->missions[3].sword_recovered = false;
 }

 void run_game_loop(GameData *data){
    if(data == NULL) return;

    srand((unsigned int)time(NULL));

    data->save_list_head = NULL;
    
    data->cheats_unlocked = false;

    display_initial_menu(data);

    printf("\n[System] Game application terminated. Goodbye!\n");
 }