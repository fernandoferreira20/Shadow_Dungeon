 /**
 * @file game_engine.c
 * @brief Initialize a new game state and runs the logic
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h> 

#include "game_engine.h"
#include "game_types.h"
#include "world/village.h"
#include "world/dungeon.h"
#include "utils/utils.h"
#include "entities/player.h"

void initialize_data(GameData *data){
    if(data == NULL) return;

    // Safety: Clear everything first
    memset(data, 0, sizeof(GameData));

    // Reset hero stats
    data->current_hero.life_points = MAX_LIFE;
    data->current_hero.coins = 0;
    data->current_hero.potions_count = 0;

    // Initialize Missions (using the enum values 0-3)
    for(int i = 0; i < MAX_MISSIONS; i++){
        data->missions[i].type = (MissionType)i;
        data->missions[i].is_completed = false;
    }
    
    // Specific setup if needed
    data->save_list_head = NULL;
    data->cheats_unlocked = false;
}

void run_game_loop(GameData *data){
    if(data == NULL) return;

    srand((unsigned int)time(NULL));
    bool game_running = true;

    printf("\n[System] Entering the world of Shadow Dungeon...\n");
    
    // === THE MAIN GAME LOOP ===
    while(game_running) {
        
        // 1. Enter Village and wait for user choice
        int mission_id = enter_village(data);

        // 2. Handle Exit
        if(mission_id == -1) {
            game_running = false;
            break;
        }

        // 3. Handle Mission Start
        MissionType m_type = (MissionType)mission_id;
        
        // Generate the dungeon
        Dungeon current_dungeon = create_dungeon(m_type);
        MissionStatus *current_status = &data->missions[mission_id];

        printf("\n--- MISSION START: %d ---\n", mission_id);
        press_enter_to_continue();

        // 4. Dungeon Loop (Room by Room)
        while(current_dungeon.current_room_index < MAX_DUNGEON_ROOMS) {
            
            process_current_room(&current_dungeon, &data->current_hero, current_status);

            // Check Game Over
            if(is_hero_dead(&data->current_hero)) {
                printf("\n\n=== GAME OVER ===\n");
                printf("Your hero has fallen.\n");
                printf("You are dragged back to the village by friendly travelers.\n");
                printf("Cost: %d coins.\n", COST_TO_RETURN_VILLAGE);
                
                // Penalty
                data->current_hero.life_points = 1; 
                data->current_hero.coins -= COST_TO_RETURN_VILLAGE;
                if(data->current_hero.coins < 0) data->current_hero.coins = 0;
                
                press_enter_to_continue();
                break; // Break dungeon loop, go back to village
            }
        }

        // 5. Mission Complete Check (End of Dungeon)
        if(current_dungeon.current_room_index >= MAX_DUNGEON_ROOMS) {
            printf("\n--- DUNGEON CLEARED ---\n");
            printf("You return to the village safely.\n");
            
            if(m_type == MISSION_SWAMP || m_type == MISSION_MANSION){
                current_status->is_completed = true;
            }
            
            press_enter_to_continue();
        }
    }

    printf("\n[System] Game application terminated. Goodbye!\n");
}