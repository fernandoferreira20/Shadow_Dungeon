/**
 * @file gamedata.c
 * @author Fernando 908697
 * @brief Implementation of game state management, handling the transfer of data between active game memory and save structures
 */

 #include "game_data.h"
 #include <stddef.h> // for NULL

void load_game_data(GameData *data, const SaveData *save){
    if(data == NULL || save == NULL){
        return;
    }

    // copy the hero stats
    data->current_hero = save->hero_snapshot;

    // copy mission progess
    for(int i = 0; i < 4; i++){
        data->missions[i] = save->mission_snapshot[i];
    }
}

SaveData create_save_data(const GameData *data){
    SaveData save;

    // copy current state into the save object
    save.hero_snapshot = data->current_hero;

    // update simple counters for the save summary
    save.life_points = data->current_hero.life_points;
    save.coins = data->current_hero.coins;

    // calculate total items (points + key + sword + armor, etc)
    save.items_count = data->current_hero.potions_count;
    if(data->current_hero.has_sword) save.items_count++;
    if(data->current_hero.has_armor) save.items_count++;
    if(data->current_hero.has_key) save.items_count++;

    // copy missions
    save.completed_missions_count = 0;
    for(int i = 0; i < 4; i++){
        save.mission_snapshot[i] = data->missions[i];
        if(data->missions[i].is_completed){
            save.completed_missions_count++;
        }
    }
    return save;
}