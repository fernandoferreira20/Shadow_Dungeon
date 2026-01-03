/**
 * @file cheats.c
 * @author Otajon 908553
 * @brief Implementation of cheating menu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cheats.h"
#include "game_types.h"
#include "utils/utils.h" // Use this for consistent input!

// Key Sequence: W, W, S, S, A, D, A, D, B, A
static const char konami_sequence[] = {'w', 'w', 's', 's', 'a', 'd', 'a', 'd', 'b', 'a'};
static int konami_position = 0;

void check_konami_code(GameData *data, char input) {
    if (data->cheats_unlocked) return;
    
    if (input == konami_sequence[konami_position]) {
        konami_position++;
        
        if (konami_position == 10) {
            data->cheats_unlocked = true;
            printf("\n[System] ??? A strange power awakens... CHEATS UNLOCKED! ???\n");
            press_enter_to_continue();
        }
    } else {
        // Reset if wrong key, but allow restart immediately if key is 'w'
        if (input == 'w') konami_position = 1;
        else konami_position = 0;
    }
}

void display_cheats_menu(GameData *data) {
    if (!data->cheats_unlocked) {
        printf("Cheats are locked! Enter Konami code in Main Menu to unlock.\n");
        return;
    }
    
    while (1) {
        printf("\n=== GOD MODE MENU ===\n");
        printf("Hero: %d HP, %d Coins\n", data->current_hero.life_points, data->current_hero.coins);
        printf("1. Set Life Points\n");
        printf("2. Set Coins\n");
        printf("3. Unlock All Missions\n");
        printf("4. Get All Items\n");
        printf("0. Exit\n");
        
        // Use standard input to avoid bugs
        int choice = get_int_input("Choose: ", 0, 4);
        
        if (choice == 1) {
            int hp = get_int_input("Enter HP (1-100): ", 1, 100);
            data->current_hero.life_points = hp;
            printf("HP set to %d.\n", hp);
        } else if (choice == 2) {
            int coins = get_int_input("Enter Coins: ", 0, 99999);
            data->current_hero.coins = coins;
            printf("Coins set to %d.\n", coins);
        } else if (choice == 3) {
            for (int i = 0; i < 4; i++) data->missions[i].is_completed = true;
            printf("All missions unlocked.\n");
        } else if (choice == 4) {
            data->current_hero.has_sword = true;
            data->current_hero.has_hero_sword = true;
            data->current_hero.has_armor = true;
            data->current_hero.has_key = true;
            printf("Inventory full.\n");
        } else if (choice == 0) {
            return;
        }
        press_enter_to_continue();
    }
}