/**
* @file missions.c
* @author Fernado 908697
* @brief Implementation of mission logic.
*/

#include "missions.h"
#include "utils/utils.h" 
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
    
    printf("\n--- MISSION SELECTION ---\n");
    printf("1. Rotting Swamp %s\n", data->missions[0].is_completed ? "[COMPLETED]" : "");
    printf("2. Haunted Mansion %s\n", data->missions[1].is_completed ? "[COMPLETED]" : "");
    printf("3. Crystal Cave %s\n", data->missions[2].is_completed ? "[COMPLETED]" : "");

    // Logic: Only show final boss if previous 3 are done
    bool all_completed = data->missions[0].is_completed && 
                         data->missions[1].is_completed && 
                         data->missions[2].is_completed;

    if(all_completed){
        printf("4. The Dark Lord's Castle\n");
    }

    printf("0. Back / Cancel\n");

    int max_choice = all_completed ? 4 : 3;
    
    // CORRECTION HERE: We declare 'choice' here for the first time
    int choice = get_int_input("Choose your destination: ", 0, max_choice);

    return choice; 
}

void mark_mission_complete(MissionStatus *mission){
    if(mission != NULL){
        mission->is_completed = true;
    }
}