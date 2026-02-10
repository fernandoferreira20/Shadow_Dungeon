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
#include "utils/utils.h" 
#include "menus/menus.h" 

// Key Sequence: W, W, S, S, A, D, A, D, B, A
static const char konami_sequence[] = {'w', 'w', 's', 's', 'a', 'd', 'a', 'd', 'b', 'a', ' '};
static int konami_position = 0;

void check_konami_code(GameData *data, char input) {
    if (data->cheats_unlocked) return;
    
    if (input == konami_sequence[konami_position]) {
        konami_position++;
        
        if (konami_position == 10) {
            data->cheats_unlocked = true;
            // Matrix-style system message
            printf("\n" BOLD_GREEN "[System] ??? A strange power awakens... " BOLD_MAGENTA "CHEATS UNLOCKED!" BOLD_GREEN " ???\n" COLOR_RESET);
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
        printf(BOLD_RED " [!] Cheats are locked! Enter Konami code in Main Menu to unlock.\n" COLOR_RESET);
        return;
    }
    
    // display list of saves to hack
    if(data->save_list_head == NULL){
        print_header("CHEAT MENU");
        printf(BOLD_RED " No saved games found to modify!\n" COLOR_RESET);
        printf(" Start a game and save it first.\n");
        press_enter_to_continue();
        return;
    }

    clear_input_buffer();
    print_header("SELECT SAVE TO HACK");

    SaveNode *current = data->save_list_head;
    int count = 1;

    // print all saves
    while(current != NULL){
        printf(BOLD_WHITE " [%d]" COLOR_RESET " %s (HP: " BOLD_GREEN "%d" COLOR_RESET " | Coins: " BOLD_YELLOW "%d" COLOR_RESET ")\n", 
               count, 
               current->data.date_time, 
               current->data.hero_snapshot.life_points, 
               current->data.hero_snapshot.coins);
        current = current->next;
        count++;
    }
    print_divider();
    printf(BOLD_WHITE " [0]" COLOR_RESET " Cancel\n");

    int save_choice = get_int_input("Select save: ", 0, count - 1);
    if(save_choice == 0) return;

    // find the selected save node
    SaveNode *target_save = data->save_list_head;
    int current_index = 1;
    while(target_save != NULL && current_index < save_choice){
        target_save = target_save->next;
        current_index++;
    } 

    if(target_save == NULL) return; 

    // edit the target save
    while(1){
        clear_input_buffer();
        char title[50];
        sprintf(title, "HACKING SAVE #%d", save_choice);
        print_header(title);
        
        printf(" Target: %s\n", target_save->data.date_time);
        printf(" Current Stats: " BOLD_GREEN "%d HP" COLOR_RESET " | " BOLD_YELLOW "%d Coins" COLOR_RESET "\n",
            target_save->data.hero_snapshot.life_points,
            target_save->data.hero_snapshot.coins);
            
        print_divider();
        printf(BOLD_WHITE " [1]" COLOR_RESET " Set Life Points\n");
        printf(BOLD_WHITE " [2]" COLOR_RESET " Set Coins\n");
        printf(BOLD_WHITE " [3]" COLOR_RESET " Unlock Final Missions\n");
        printf(BOLD_WHITE " [0]" COLOR_RESET " Save & Exit Cheats\n");

        int action = get_int_input("Choose hack: ", 0, 3);

        if(action == 1){
            int hp = get_int_input(BOLD_CYAN "Enter new HP (1 - 999): " COLOR_RESET, 1, 999);
            target_save->data.hero_snapshot.life_points = hp;
            printf(BOLD_GREEN " >> HP updated in save file.\n" COLOR_RESET);
        }else if(action == 2){
            int coins = get_int_input(BOLD_CYAN "Enter new Coins (0 - 999): " COLOR_RESET, 0, 999);
            target_save->data.hero_snapshot.coins = coins;
            printf(BOLD_GREEN " >> Coins updated in save file.\n" COLOR_RESET);
        }else if(action == 3){
            // To unlock final mission, we must complete Swamp(0), Mansion(1), Cave(2)
            for(int i = 0; i < 3; i++){
                target_save->data.mission_snapshot[i].is_completed = true;
            }
            target_save->data.completed_missions_count = 3;
            printf(BOLD_MAGENTA " >> Missions 1-3 marked complete. Castle unlocked!\n" COLOR_RESET);
        }else if(action == 0){
            break;
        }
        press_enter_to_continue();
    }
}