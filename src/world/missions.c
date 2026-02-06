/**
* @file missions.c
* @author Fernado 908697
* @brief Implementation of mission logic.
*/

#include "missions.h"
#include "utils/utils.h" 
#include "menus/menus.h" 
#include <stdio.h>

void initialize_missions(MissionStatus missions[4]){
    // 0: Swamp, 1: Mansion, 2: Cave, 3: Castle
    for(int i = 0; i < 4; i++){
        missions[i].type = (MissionType)i; 
        missions[i].is_completed = false;
        missions[i].progress_counter = 0;
        missions[i].key_recovered = false;
        missions[i].sword_recovered = false;
    }
}

int select_mission(const GameData *data){
    
    print_header("MISSION SELECTION");
    
    // Using ternary operators inside printf for color coding
    printf(BOLD_WHITE " [1]" COLOR_RESET " Rotting Swamp    %s\n", 
           data->missions[0].is_completed ? BOLD_GREEN "[COMPLETED]" COLOR_RESET : "");
           
    printf(BOLD_WHITE " [2]" COLOR_RESET " Haunted Mansion  %s\n", 
           data->missions[1].is_completed ? BOLD_GREEN "[COMPLETED]" COLOR_RESET : "");
           
    printf(BOLD_WHITE " [3]" COLOR_RESET " Crystal Cave     %s\n", 
           data->missions[2].is_completed ? BOLD_GREEN "[COMPLETED]" COLOR_RESET : "");

    // Logic: Only show final boss if previous 3 are done
    bool all_completed = data->missions[0].is_completed && 
                         data->missions[1].is_completed && 
                         data->missions[2].is_completed;

    if(all_completed){
        print_divider();
        printf(BOLD_WHITE " [4]" COLOR_RESET BOLD_MAGENTA " The Dark Lord's Castle" COLOR_RESET "\n");
    }

    print_divider();
    printf(BOLD_WHITE " [0]" COLOR_RESET " Back / Cancel\n");

    int max_choice = all_completed ? 4 : 3;
    
    int choice = get_int_input("Choose your destination: ", 0, max_choice);

    return choice; 
}

void mark_mission_complete(MissionStatus *mission){
    if(mission != NULL){
        mission->is_completed = true;
    }
}