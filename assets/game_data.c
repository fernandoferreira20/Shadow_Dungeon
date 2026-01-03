 /**
 * @file game_data.c
 * @author Fernando 908697
 * @brief Implementation of game state management.
 */

 #include "game_data.h"
 #include <stddef.h> // for NULL
#include <string.h> // for memset, strftime
#include <time.h>   // for time, localtime

void load_game_data(GameData *data, const SaveData *save){
    if(data == NULL || save == NULL){
        return;
    }

    // copy the hero stats
    data->current_hero = save->hero_snapshot;

    // copy mission progess
    for(int i = 0; i < MAX_MISSIONS; i++){
        data->missions[i] = save->mission_snapshot[i];
    }
}

SaveData create_save_data(const GameData *data){
    SaveData save;

    // Safety: Clear memory to avoid garbage data in padding bytes
    memset(&save, 0, sizeof(SaveData));

    if(data == NULL){
        return save; // return empty struct
    }

    // 1. copy the Hero state
    save.hero_snapshot = data->current_hero;

    // 2. copy missions and current count completion
    save.completed_missions_count = 0;

    for(int i = 0; i < MAX_MISSIONS; i++){
        save.mission_snapshot[i] = data->missions[i];
        if(data->missions[i].is_completed){
            save.completed_missions_count++;
        }
    }

    // 3. genearte Timestamp
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Format: "YYYY-MM-DD HH:MM:SS"
    if(t != NULL){
        strftime(save.date_time, sizeof(save.date_time), "%Y-%m-%d %H:%M:%S", t);
    }else{
        // Fallback if time fails
        strncpy(save.date_time, "Unknown Date", sizeof(save.date_time) - 1);
    }

    return save;
}