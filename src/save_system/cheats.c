/**
 * @file cheat.c
 * @author Otajon 908553
 * @brief implementation of cheating menu, building konami code
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cheats.h"
#include "../../include/game_types.h"

/* Konami code sequence */
static const char konami_sequence[] = {'w', 'w', 's', 's', 'a', 'd', 'a', 'd', 'b', 'a', ' '};
static int konami_position = 0;

void check_konami_code(GameData *data, char input) {
    /* If unlocked, no check */
    if (data->cheats_unlocked) {
        return;
    }
    
    /* Check if input matches next Konami code character */
    if (konami_position < 11 && input == konami_sequence[konami_position]) {
        konami_position++;
        
        /* if all input matches, unlock! */
        if (konami_position == 11) {
            data->cheats_unlocked = true;
            printf("\n🎉 Konami Code accepted! Cheats unlocked!\n");
        }
    } else {
        /* Wrong input, reset to 0 */
        konami_position = 0;

    }
}

void display_cheats_menu(GameData *data) {
    int choice;
    char input[100];
    
    if (!data->cheats_unlocked) {
        printf("Cheats are locked! Enter Konami code to unlock.\n");
        return;
    }
    
    while (1) {
        printf("\n=== CHEATS MENU ===\n");
        printf("Current Hero: %d HP, %d coins\n", 
               data->current_hero.life_points, 
               data->current_hero.coins);
        printf("1. Modify Hero Life Points\n");
        printf("2. Modify Hero Coins\n");
        printf("3. Unlock Final Mission (Castle)\n");
        printf("4. Exit Cheats Menu\n");
        printf("Choose option [1-4]: ");
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &choice) == 1) {
                switch (choice) {
                    case 1: /* Modification of HP */
                        printf("Enter new Life Points (1-100): ");
                        if (fgets(input, sizeof(input), stdin) != NULL) {
                            int new_hp;
                            if (sscanf(input, "%d", &new_hp) == 1 && new_hp >= 1 && new_hp <= 100) {
                                data->current_hero.life_points = new_hp;
                                printf("Life Points set to %d\n", new_hp);
                            } else {
                                printf("Invalid value!\n");
                            }
                        }
                        break;
                        
                    case 2: /* Modify coins */
                        printf("Enter new Coins amount (0-9999): ");
                        if (fgets(input, sizeof(input), stdin) != NULL) {
                            int new_coins;
                            if (sscanf(input, "%d", &new_coins) == 1 && new_coins >= 0) {
                                data->current_hero.coins = new_coins;
                                printf("Coins set to %d\n", new_coins);
                            } else {
                                printf("Invalid value!\n");
                            }
                        }
                        break;
                        
                    case 3: /* Unlock final mission */
                        printf("Final mission (Dark Lord's Castle) unlocked!\n");
                        /* Mark all regular missions as completed */
                        for (int i = 0; i < 3; i++) {
                            data->missions[i].is_completed = true;
                        }
                        break;
                        
                    case 4: /* Exit */
                        return;
                        
                    default:
                        printf("Invalid choice!\n");
                }
            }
        }
        
        printf("Press Enter to continue...");
        while (getchar() != '\n');
    }
}