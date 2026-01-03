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

 bool return_to_village(Hero *hero, const MissionStatus *status){
    //check the mission criteria
    bool criteria_met = false;

    //Rotting Swamp: Defeat 3 Orc Generals
    if(status->type == MISSION_SWAMP && status->progress_counter >= 3) criteria_met = true;
    //Haunted Mansion: Recover Key and Defeat the Vampire
    else if(status->type == MISSION_MANSION) {
        if(status->is_completed && status->key_recovered) criteria_met = true;
    }
    //Crystal Cave: Recover Hero's Sword
    else if (status->type == MISSION_CAVE){
        if(status->sword_recovered) criteria_met = true;
    }

    //When the mission is successful
    if(criteria_met){
        printf("Mission Criteria Met! Returning to village...\n");
        return true;
    }

    //When the mission failed
    printf("Mission incomplete. Pay %d to flee? (You have %d)\n", COST_TO_RETURN_VILLAGE, hero->coins);
    if(status->type == MISSION_MANSION) printf("(Status: Vampire Dead? %s. Key found? %s)\n", status->is_completed ? "Yes":"No", status->key_recovered ? "Yes":"No");
    if(status->type == MISSION_SWAMP) printf("(Status: Generals Defeated: %d/3)\n", status->progress_counter);

    int choice = get_int_input("1. Pay & Flee\n2. Stay\n> ", 1, 2);

    if(choice == 1){
        if(hero->coins >= COST_TO_RETURN_VILLAGE){
            hero->coins -= COST_TO_RETURN_VILLAGE;
            printf("You paid the smugglers and escaped to the village.\n");
            return true;
        } else {
            printf("Not enough coins! You must fight on.\n");
            return false;
        }
    }
    return false;
 }

 void display_mission_menu(Hero *hero, Dungeon *dungeon, MissionStatus *status){
    bool in_dungeon = true;

    while(in_dungeon && hero->life_points > 0){
        printf("\n=== MISSION MENU ===\n");
        printf("1. Explore Dungeon Room (%d/%d)\n", dungeon->current_room_index + 1, MAX_DUNGEON_ROOMS);
        printf("2. Shop\n");
        printf("3. Inventory\n");
        printf("4. Return to Village\n");

        int choice = get_int_input("Choose action: ", 1, 4);

        switch(choice){
            case 1: //explore
            process_current_room(dungeon, hero, status);
            break;
            case 2: //shop
            display_shop_menu(hero);
            break;
            case 3: //inventory
            display_inventory(hero);
            break;
            case 4: //return to village
            if(return_to_village(hero, status)){
                in_dungeon = false;
            }
            break;
        }

        //Force return check if dungeon ends
        if(dungeon->current_room_index >= MAX_DUNGEON_ROOMS && in_dungeon){
            printf("End of dungeon reached. You must return to the village.\n");
            if(return_to_village(hero, status)) in_dungeon = false;
        }
    }
 }