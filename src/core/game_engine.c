/**
 * @file game_engine.c
 * @author Harshit 908571
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
#include "combat/final_boss.h"
#include "menus/menus.h" 

void initialize_data(GameData *data){
    if(data == NULL) return;

    // Save the pointer to the save list so we don't lose it
    SaveNode *backup_saves = data->save_list_head;

    // Keep the cheats unlocked if they were already entered
    bool backup_cheats = data->cheats_unlocked;

    // Safety: Clear everything first 
    memset(data, 0, sizeof(GameData));

    // Restore the saved list and settings
    data->save_list_head = backup_saves;
    data->cheats_unlocked = backup_cheats;

    // Reset hero stats
    data->current_hero.life_points = MAX_LIFE;
    data->current_hero.coins = 0;
    data->current_hero.potions_count = 0;

    // Initialize missions (using the enum values 0-3)
    for(int i = 0; i < MAX_MISSIONS; i++){
        data->missions[i].type = (MissionType)i;
        data->missions[i].is_completed = false;
        // Ensure counters are reset for the new game
        data->missions[i].progress_counter = 0;
        data->missions[i].key_recovered = false;
        data->missions[i].sword_recovered = false;
    }
}

void run_game_loop(GameData *data){
    if(data == NULL) return;

    srand((unsigned int)time(NULL));
    bool game_running = true;

    // System messages get a tech-like Cyan color
    printf(BOLD_CYAN "\n[System] Entering the world of Shadow Dungeon...\n" COLOR_RESET);
    
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
        MissionStatus *current_status = &data->missions[mission_id];
        
        // Handle Final Boss Mission separately
        if (m_type == MISSION_CASTLE) {
            // Verify prerequisites (Must complete previous 3 missions)
            if(!data->missions[0].is_completed || !data->missions[1].is_completed || !data->missions[2].is_completed){
                 printf(BOLD_RED " [!] You cannot enter the castle yet! Complete all other missions first.\n" COLOR_RESET);
                 press_enter_to_continue();
                 continue;
            }

            print_header(BOLD_RED "APPROACHING THE DARK LORD'S CASTLE" COLOR_RESET);
            press_enter_to_continue();

            // Trigger the Rock-Paper-Scissors Fight
            final_boss_fight(&data->current_hero);

            // Check results
            if (data->current_hero.life_points > 0) {
                // Victory logic is handled inside final_boss_fight (text), 
                // here we just end the game loop.
                game_running = false; 
            } else {
                // Defeat logic
                printf(BOLD_RED " You have been defeated by the Dark Lord.\n" COLOR_RESET);
                // Apply death penalty
                data->current_hero.life_points = 1;
                data->current_hero.coins = 0;
            }
            press_enter_to_continue();
            
            // Skip the standard dungeon generation below
            continue; 
        }

        // ==========================================================
        // STANDARD DUNGEON LOGIC (Swamp, Mansion, Cave)
        // ==========================================================

        // Generate the procedural dungeon
        Dungeon current_dungeon = create_dungeon(m_type);

        // Use the header style for consistency
        char title_buf[50];
        sprintf(title_buf, "MISSION START: %d", mission_id);
        print_header(title_buf);
        
        press_enter_to_continue();

        // 4. Dungeon Loop (Room by Room)
        while(current_dungeon.current_room_index < MAX_DUNGEON_ROOMS) {
            
            process_current_room(&current_dungeon, &data->current_hero, current_status);

            // Check for Hero Death
            if(is_hero_dead(&data->current_hero)) {
                print_header(BOLD_RED "GAME OVER" COLOR_RESET);
                printf(BOLD_WHITE " Your hero has fallen.\n" COLOR_RESET);
                printf(" You are dragged back to the village by friendly travelers.\n");
                printf(" Cost: " BOLD_YELLOW "%d coins" COLOR_RESET ".\n", COST_TO_RETURN_VILLAGE);
                
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
            print_header(BOLD_GREEN "DUNGEON CLEARED" COLOR_RESET);
            printf(" You return to the village safely.\n");
            
            // If the hero survived the forced encounters, the mission is complete
            if(m_type == MISSION_SWAMP || m_type == MISSION_MANSION || m_type == MISSION_CAVE){
                current_status->is_completed = true;
            }
            
            press_enter_to_continue();
        }
    }

    printf(BOLD_CYAN "\n[System] Game application terminated. Goodbye!\n" COLOR_RESET);
}