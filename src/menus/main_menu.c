/**
 * @file main_menu.c
 * @author Otajon 908553
 * @brief implementation of main menu, calling helper functions, and konami code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_types.h"
#include "core/game_engine.h"
#include "save_system/save_manager.h"
#include "save_system/cheats.h"    
#include "menus/menus.h"          
#include "menus/main_menu.h"
#include "utils/utils.h" 

void display_initial_menu(GameData *data) {
    char user_input[100];
    
    while (1) {
        clear_screen();                    
        print_header("Initial Game Menu");
        
        // I'm using Bold White for the brackets to guide the eye to the key commands.
        printf(BOLD_WHITE " [1]" COLOR_RESET " New Game\n");          
        printf(BOLD_WHITE " [2]" COLOR_RESET " Load Game\n");         
        
        if (data->cheats_unlocked) {
            // Cheats get a special color so you feel rewarded for unlocking them.
            printf(BOLD_YELLOW " [3] Cheats (Unlocked!)" COLOR_RESET "\n");
        }
        
        int max_choice = data->cheats_unlocked ? 3 : 2;
        printf("\nChoose an action " BOLD_CYAN "[1-%d]" COLOR_RESET ": ", max_choice);
        
        if (fgets(user_input, sizeof(user_input), stdin) != NULL) {
            int choice;
            
            if (sscanf(user_input, "%d", &choice) == 1) {
                if (choice == 1) {
                    handle_new_game(data);
                } else if (choice == 2) {
                    display_load_game_menu(data);
                } else if (choice == 3 && data->cheats_unlocked) {
                    display_cheats_menu(data);
                } else {
                    printf(BOLD_RED "Invalid choice! Please choose 1-%d.\n" COLOR_RESET, max_choice);
                    press_enter_to_continue();
                }
            } 
            else {
                if (strlen(user_input) > 0) {
                    check_konami_code(data, user_input[0]);
                }
            }
        }
    }
}

void handle_new_game(GameData *data) {
    clear_screen();
    print_header("NEW GAME");              
    printf("Hero created with:\n");
    // Highlighting the starting stats makes the player feel stronger immediately.
    printf("- " BOLD_GREEN "%d" COLOR_RESET " life points\n", MAX_LIFE);
    printf("- " BOLD_YELLOW "0" COLOR_RESET " coins\n");
    printf("- 0 items\n");
    printf("- 0 completed missions\n\n");
    
    press_enter_to_continue();
    
    initialize_data(data);
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
            // This is a big one: Color coding stats makes comparing saves much faster.
            // Green for Life, Yellow for Money.
            printf(BOLD_WHITE "%d." COLOR_RESET " %s | " BOLD_GREEN "HP: %d" COLOR_RESET " | " BOLD_YELLOW "Coin: %d" COLOR_RESET " | Missions: %d\n",
                   save_count,
                   current->data.date_time,
                   current->data.hero_snapshot.life_points,
                   current->data.hero_snapshot.coins,
                   current->data.completed_missions_count);
            current = current->next;
        }
        
        if (save_count == 0) {
            printf(COLOR_RED "No saved games found.\n" COLOR_RESET);
        }
        
        print_divider();                    
        printf(BOLD_WHITE "%d." COLOR_RESET " Back to Main Menu\n", save_count + 1);
        
        int choice = get_int_input("Select a save: ", 1, save_count + 1);
        
        if (choice == save_count + 1) {
            return;
        }
        
        clear_screen();
        printf("Selected Save #%d\n", choice);
        printf(BOLD_WHITE " [1]" COLOR_RESET " Load\n");
        printf(BOLD_WHITE " [2]" COLOR_RESET " Delete\n");
        printf(BOLD_WHITE " [3]" COLOR_RESET " Cancel\n");
        
        int action = get_int_input("Action: ", 1, 3);
        
        if (action == 1) {
            if (load_save(data, choice)) {
                printf(BOLD_GREEN "Game loaded successfully!\n" COLOR_RESET);
                press_enter_to_continue();
                run_game_loop(data); 
                return;
            } else {
                printf(BOLD_RED "Failed to load game.\n" COLOR_RESET);
                press_enter_to_continue();
            }
        } else if (action == 2) {
            printf(BOLD_RED "Are you sure you want to delete this save? (1=Yes, 0=No): " COLOR_RESET);
            int confirm = get_int_input("", 0, 1);
            
            if (confirm == 1) {
                if (delete_save(data, choice)) {
                    printf(BOLD_RED "Save deleted.\n" COLOR_RESET);
                } else {
                    printf("Failed to delete.\n");
                }
            } else {
                printf("Delete cancelled.\n");
            }
            press_enter_to_continue();
        }
    }
}