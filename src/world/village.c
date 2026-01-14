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

void display_village_menu(const GameData *data){
    if(data == NULL) return;

    printf("\n=============================\n");
    printf("         VILLAGE HUB         \n");
    printf("=============================\n");
    printf("Hero Stats: HP %d/%d | Coins: %d\n", data->current_hero.life_points, MAX_LIFE, data->current_hero.coins);

    if(data->current_hero.has_sword) printf("[Equipped: Iron Sword]\n");
    if(data->current_hero.has_hero_sword) printf("[Equipped: HERO SWORD]\n");

    printf("-----------------------------\n");
    printf("1. Start a Mission\n");   
    printf("2. Rest (Restore Life)\n");   
    printf("3. Inventory / Shop\n");   
    printf("4. Save Game\n");   
    printf("5. Exit Game\n");   
    printf("-----------------------------\n");
}

void rest_in_village(Hero *hero){
    if(hero == NULL) return;
    
    // Restore to MAX_LIFE
    hero->life_points = MAX_LIFE;
    
    printf("\n[Innkeeper]: You look tired, traveler. Take a rest here.\n");
    printf("* You slept soundly. Your health is fully restored to %d HP! *\n", MAX_LIFE);
}

void perform_exit_sequence(GameData *data){
    (void)data;
    printf("\n-----------------------------\n");
    printf("Leaving the world...\n");
    printf("Remember to save the game so you do not lose your progress!\n");
    printf("Goodbye, Hero.\n");
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
                int shop_choice = get_int_input("> ", 0, 1);
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
                perform_exit_sequence(data);
                return -1; // Signal to exit the entire program

            default:
                break;
        }
    }
}