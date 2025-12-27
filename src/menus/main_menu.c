/**
 * @file main_menu.c
 * @author Otajon 908553
 * @brief implementation of main menu, calling helper functions, and konami code
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/game_types.h"
#include "core/game_engine.h"
#include "save_system/save_manager.h"
#include "menus/menus.h"          
#include "menus/main_menu.h"


static char konami_code[] = {'w', 'w', 's', 's', 'a', 'd', 'a', 'd', 'b', 'a', ' '};
static int konami_step = 0;
static int cheats_unlocked = 0;


/* Helper functions */
static void wait_for_enter() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
    getchar();
}

static int get_number(int min, int max) {
    int num;
    char input[100];
    
    while (1) {
        printf("[%d-%d]: ", min, max);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }
        
        if (sscanf(input, "%d", &num) == 1) {
            if (num >= min && num <= max) {
                return num;
            }
        }
        
        printf("Invalid. Please enter %d-%d.\n", min, max);
    }
}

static void check_konami(char input_char) {
    if (konami_step < 11 && input_char == konami_code[konami_step]) {
        konami_step++;
        if (konami_step == 11) {
            cheats_unlocked = 1;
            printf("Cheats unlocked!\n");
        }
    } else {
        konami_step = 0;
    }
}

/* ========== 3 FUNCTIONS ========== */

void display_initial_menu(GameData *data) {
    char user_input[100];
    
    while (1) {
        clear_screen();                    
        print_header("Initial Game Menu");
        printf("1. New Game");
        printf("2. Load Game");
        
        if (cheats_unlocked) {
            printf("3. Cheats\n");
        }
        
        int max_choice = cheats_unlocked ? 3 : 2;
        printf("Choose an action [1-%d]: ", max_choice);
        
        if (fgets(user_input, sizeof(user_input), stdin) != NULL) {
            if (strlen(user_input) == 2 && user_input[1] == '\n') {
                check_konami(user_input[0]);
                continue;
            }
            
            int choice;
            if (sscanf(user_input, "%d", &choice) == 1) {
                if (choice == 1) {
                    handle_new_game(data);
                } else if (choice == 2) {
                    display_load_game_menu(data);
                } else if (choice == 3 && cheats_unlocked) {
                    printf("Cheats menu coming soon!\n");
                    wait_for_enter();
                } else {
                    printf("Invalid choice!\n");
                    wait_for_enter();
                }
            } else {
                printf("Please enter a number.\n");
                wait_for_enter();
            }
        }
    }
}

void handle_new_game(GameData *data) {
    clear_screen();
    print_header("NEW GAME");              
    printf("Hero created with:\n");
    printf("- 20 life points\n");
    printf("- 0 coins\n");
    printf("- 0 items\n");
    printf("- 0 completed missions\n\n");
    
    wait_for_enter();
    
    initialize_game(data);
    run_game_loop(data);
}

void display_load_game_menu(GameData *data) {
    while (1) {
        clear_screen();
        print_header("LOAD GAME");         
        
        SaveNode *saves = get_save_list(data);
        int save_count = 0;
        
        SaveNode *current = saves;
        while (current != NULL) {
            save_count++;
            printf("%d. %s, %d L. POINTS, %d COINS, %d ITEMS, %d COMPLETED MISSIONS\n",
                   save_count,
                   current->data.data_time,
                   current->data.life_points,
                   current->data.coins,
                   current->data.items_count,
                   current->data.completed_missions_count);
            current = current->next;
        }
        
        if (save_count == 0) {
            printf("No saved games found.\n");
        }
        
        print_divider();                    
        printf("%d. Back to Main Menu\n", save_count + 1);
        printf("Select a game [1-%d]: ", save_count + 1);
        
        int choice = get_number(1, save_count + 1);
        
        if (choice == save_count + 1) {
            return;
        }
        
        clear_screen();
        printf("1. Load\n");
        printf("2. Delete\n");
        printf("Insert the action [1-2]: ");
        
        int action = get_number(1, 2);
        
        if (action == 1) {
            if (load_save(data, choice)) {
                printf("Game loaded successfully!\n");
                wait_for_enter();
                run_game_loop(data);
                return;
            } else {
                printf("Failed to load game.\n");
                wait_for_enter();
            }
        } else {
            printf("Are you sure you want to permanently delete the save? [Y/N]: ");
            char answer[10];
            fgets(answer, sizeof(answer), stdin);
            
            if (answer[0] == 'Y' || answer[0] == 'y') {
                if (delete_save(data, choice)) {
                    printf("Save deleted.\n");
                } else {
                    printf("Failed to delete.\n");
                }
            } else {
                printf("Delete cancelled.\n");
            }
            wait_for_enter();
        }
    }
}