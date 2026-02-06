/**
 * @file mission_menu.c
 * @author Alexandru 907625
 * @brief Implementation of the In-Mission Menu
 */

 #include <stdio.h>
 #include "mission_menu.h"
 #include "utils/utils.h"
 #include "items/inventory.h"
 #include "items/shop.h"
 #include "menus/menus.h" // Added to access print_header/divider

 bool return_to_village(Hero *hero, const MissionStatus *status){
    bool criteria_met = false;

    if(status->type == MISSION_SWAMP && status->progress_counter >= 3) criteria_met = true;
    else if(status->type == MISSION_MANSION) {
        if(status->is_completed && status->key_recovered) criteria_met = true;
    }
    else if (status->type == MISSION_CAVE){
        if(status->sword_recovered) criteria_met = true;
    }

    if(criteria_met){
        // Victory! Make it Green and Bold.
        printf(BOLD_GREEN "Mission Criteria Met! Returning to village...\n" COLOR_RESET);
        return true;
    }

    // Failure / Retreat state
    printf(BOLD_RED "Mission incomplete." COLOR_RESET " Pay " BOLD_YELLOW "%d" COLOR_RESET " to flee? (You have " BOLD_YELLOW "%d" COLOR_RESET ")\n", COST_TO_RETURN_VILLAGE, hero->coins);
    
    if(status->type == MISSION_MANSION) printf("(Status: Vampire Dead? %s. Key found? %s)\n", status->is_completed ? "Yes":"No", status->key_recovered ? "Yes":"No");
    if(status->type == MISSION_SWAMP) printf("(Status: Generals Defeated: %d/3)\n", status->progress_counter);

    int choice = get_int_input("1. Pay & Flee\n2. Stay\n> ", 1, 2);

    if(choice == 1){
        if(hero->coins >= COST_TO_RETURN_VILLAGE){
            hero->coins -= COST_TO_RETURN_VILLAGE;
            printf(BOLD_YELLOW "You paid the smugglers and escaped to the village.\n" COLOR_RESET);
            return true;
        } else {
            printf(BOLD_RED "Not enough coins! You must fight on.\n" COLOR_RESET);
            return false;
        }
    }
    return false;
 }

 void display_mission_menu(Hero *hero, Dungeon *dungeon, MissionStatus *status){
    bool in_dungeon = true;

    while(in_dungeon && hero->life_points > 0){
        print_header("MISSION MENU"); // Use the consistent header style
        
        // Highlight the progress counter so the player knows how far they are
        printf(BOLD_WHITE " [1]" COLOR_RESET " Explore Dungeon Room (" BOLD_CYAN "%d/%d" COLOR_RESET ")\n", dungeon->current_room_index + 1, MAX_DUNGEON_ROOMS);
        printf(BOLD_WHITE " [2]" COLOR_RESET " Shop\n");
        printf(BOLD_WHITE " [3]" COLOR_RESET " Inventory\n");
        printf(BOLD_WHITE " [4]" COLOR_RESET " Return to Village\n");

        int choice = get_int_input("Choose action: ", 1, 4);

        switch(choice){
            case 1: 
            process_current_room(dungeon, hero, status);
            break;
            case 2: 
            display_shop_menu(hero);
            break;
            case 3: 
            display_inventory(hero);
            break;
            case 4: 
            if(return_to_village(hero, status)){
                in_dungeon = false;
            }
            break;
        }

        if(dungeon->current_room_index >= MAX_DUNGEON_ROOMS && in_dungeon){
            printf(BOLD_CYAN "End of dungeon reached. You must return to the village.\n" COLOR_RESET);
            if(return_to_village(hero, status)) in_dungeon = false;
        }
    }
 }