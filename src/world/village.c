/**
* @file village.c
* @author Fernado 908697
* @brief Implementation of the central hub mechanics.
*/

#include <stdio.h>
#include <stddef.h> 
#include "village.h"
#include "save_system/save_manager.h"
#include "world/missions.h"
#include "utils/utils.h"
#include "items/inventory.h"
#include "items/shop.h" 
#include "menus/menus.h" 

void display_village_menu(const GameData *data){
    if(data == NULL) return;

    clear_screen(); 
    // Replaced manual ascii lines with the consistent project header
    print_header("VILLAGE HUB");

    // Stats Line: Using BOLD colors to make the numbers pop out
    printf(" " BOLD_WHITE "[ STATUS ]" COLOR_RESET " %sHP %d/%d%s | %sCoins: %d%s\n", 
           BOLD_GREEN, data->current_hero.life_points, MAX_LIFE, COLOR_RESET,
           BOLD_YELLOW, data->current_hero.coins, COLOR_RESET);
    
    // Equipment Status
    if(data->current_hero.has_hero_sword) {
        printf(" " BOLD_WHITE "[ WEAPON ]" COLOR_RESET " %sHERO SWORD%s (Legendary)\n", BOLD_MAGENTA, COLOR_RESET);
    }else if(data->current_hero.has_sword){ 
        printf(" " BOLD_WHITE "[ WEAPON ]" COLOR_RESET " %sIron Sword%s\n", BOLD_CYAN, COLOR_RESET);
    }

    // Show Key/Armor status if relevant
    if(data->current_hero.has_key) printf(" " BOLD_WHITE "[ ITEM ]" COLOR_RESET "   %sCastle Key%s\n", BOLD_BLUE, COLOR_RESET);

    print_divider();
    printf(BOLD_WHITE " [1]" COLOR_RESET " Start a Mission\n");   
    printf(BOLD_WHITE " [2]" COLOR_RESET " Rest (Restore Life)\n");   
    printf(BOLD_WHITE " [3]" COLOR_RESET " Inventory / Shop\n");   
    printf(BOLD_WHITE " [4]" COLOR_RESET " Save Game\n");   
    printf(BOLD_WHITE " [5]" COLOR_RESET " Exit Game\n");   
    print_divider();
}

void rest_in_village(Hero *hero){
    if(hero == NULL) return;
    
    // Restore to MAX_LIFE
    hero->life_points = MAX_LIFE;
    
    printf("\n" BOLD_CYAN "[Innkeeper]:" COLOR_RESET " \"You look tired, traveler. Take a rest here.\"\n");
    // Used Green to signify healing/safety
    printf("%s* You slept soundly. Your health is fully restored to %d HP! *%s\n", 
           BOLD_GREEN, MAX_LIFE, COLOR_RESET);
}

bool perform_exit_sequence(GameData *data){
    (void)data;
    // Red warning for destructive actions
    printf("\n%sYou are exiting the game.%s\n", BOLD_RED, COLOR_RESET);
    printf("Remember to save the game so as not to lose your progress.\n");
    printf("Are you sure to proceed? " BOLD_WHITE "[1=Yes / 0=No]" COLOR_RESET ": ");
    
    int choice = get_int_input("", 0, 1);
    
    if(choice == 1) {
        printf(BOLD_MAGENTA "Goodbye, Hero.\n" COLOR_RESET);
        return true; // Confirm Exit
    } else {
        printf(BOLD_GREEN "Exit cancelled. Returning to village.\n" COLOR_RESET);
        return false; // Cancel Exit
    }
}

// NOTE: We return 'int' now to tell the Main Engine what to do next
// 0 = Stay in village (handled internally)
// 1 = Start Mission
// -1 = Exit Game
int enter_village(GameData *data) {
    int choice = 0;
    int mission_choice = 0;

    while (1) {
        display_village_menu(data);
        choice = get_int_input("Select an option: ", 1, 5);

        switch (choice) {
            case 1:
                mission_choice = select_mission(data); 
                if(mission_choice > 0) {
                    // We return the Mission ID (adjusted to 0-index) to the Game Engine
                    // Menu shows 1..4, logic uses 0..3
                    return mission_choice - 1; 
                }
                break;

            case 2:
                rest_in_village(&data->current_hero);
                press_enter_to_continue();
                break;

            case 3:
                display_inventory(&data->current_hero);
                printf("\nWould you like to visit the shop? (1=Yes, 0=No)\n");
                int shop_choice = get_int_input(BOLD_CYAN "> " COLOR_RESET, 0, 1);
                if(shop_choice == 1) {
                    display_shop_menu(&data->current_hero);
                }
                break;

           case 4:
                // Call the save function
                save_game(data); 
                press_enter_to_continue();
                break;
                
            case 5:
                if(perform_exit_sequence(data)){
                    return -1; // exit comfirmed
                }
                break;
                // If false, the loop continues and menu reappears
            default:
                break;
        }
    }
}