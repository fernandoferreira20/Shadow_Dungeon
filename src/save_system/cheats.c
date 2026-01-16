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
    
    // display list of saves to hack
    if(data->save_list_head == NULL){
        printf("\n=== CHEAT MENU ===\n");
        printf("No saved games found to modify!\n");
        printf("Start a game and save it first.\n");
        press_enter_to_continue();
        return;
    }

    clear_input_buffer();
    printf("=== SELECT A SAVE TO MODIFY ===\n");

    SaveNode *current = data->save_list_head;
    int count = 1;

    // print all saves
    while(current != NULL){
        printf("%d. %s (HP: %d | Coins: %d)\n", count, current->data.date_time, current->data.hero_snapshot.life_points, current->data.hero_snapshot.coins);
        current = current->next;
        count++;
    }
    printf("0. Cancel\n");

    int save_choice = get_int_input("Select save: ", 0, count - 1);
    if(save_choice == 0) return;

    // find the selected save node
    SaveNode *target_save = data->save_list_head;
    int current_index = 1;
    while(target_save != NULL && current_index < save_choice){
        target_save = target_save->next;
        current_index++;
    } 

    if(target_save == NULL) return; // should not happen

    // edit the target save
    while(1){
        clear_input_buffer();
        printf("\n=== HACKING SAVE #%d ===\n", save_choice);
        printf("Target: %s\n", target_save->data.date_time);
        printf("Current Stats: %d HP | %d Coins\n",
            target_save->data.hero_snapshot.life_points,
            target_save->data.hero_snapshot.coins);
        printf("-------------------------\n");
        printf("1. Set Life Points\n");
        printf("2. Set Coins\n");
        printf("3. Unlock Final Missons\n");
        printf("0. Save & Exit Cheats\n");

        int action = get_int_input("Choose hack: ", 0, 3);

        if(action == 1){
            int hp = get_int_input("Enter new HP (1 - 999): ", 1, 999);
            target_save->data.hero_snapshot.life_points = hp;
            printf(">> HP updated in save file.\n");
        }else if(action == 2){
            int coins = get_int_input("Enter new Coins (0 - 999): ", 0, 999);
            target_save->data.hero_snapshot.coins = coins;
            printf(">> Coins updated in save file.\n");
        }else if(action == 3){
            // To unlock final mission, we must complete Swamp(0), Mansion(1), Cave(2)
            // Note: We are editing the 'mission_snapshot' inside the save
            for(int i = 0; i < 3; i++){
                target_save->data.mission_snapshot[i].is_completed = true;
            }
            // upddate the counter for the save display
            target_save->data.completed_missions_count = 3;
            printf(">> Missions 1-3 marked complete. Castle unloked!\n");
        }else if(action == 0){
            break;
        }
        press_enter_to_continue();
    }
}