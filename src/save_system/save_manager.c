/**
 * @file save_manager.c
 * @author Otajon 908553
 * @brief Save/load game state using linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> 
#include "save_manager.h"
#include "game_types.h"
#include "utils/utils.h" // Added for colors

void save_game(GameData *data) {
    if(data == NULL){
        return;
    }

    /*Allocate memory for the new node*/
    SaveNode *new_save = (SaveNode*)malloc(sizeof(SaveNode));
    if(new_save == NULL){
        printf(BOLD_RED "Error: Cannot allocate memory for save!\n" COLOR_RESET);
        return;
    }

    /*Generate Timestamp (Day-Month-Year Hour:Minute:Second)*/
    time_t now = time(NULL);
    struct tm * t = localtime(&now);
    strftime(new_save->data.date_time, MAX_STRING_LEN, "%d-%m-%Y %H:%M:%S", t);

    /*Copy Hero Stats*/
    new_save->data.hero_snapshot = data->current_hero;

    /*Copy mission progress*/
    int completed_count = 0;
    for(int i = 0; i < MAX_MISSIONS; i++){
        // copy the mission stats array
        new_save->data.mission_snapshot[i] = data->missions[i];

        // count for the complited for the save summary
        if(data->missions[i].is_completed){
            completed_count++;
        }
    }
    new_save->data.completed_missions_count = completed_count;

    /* Link to the list*/
    new_save->next = data->save_list_head;
    data->save_list_head = new_save;

    // Use Bold Green to make the player feel secure that their data is safe
    printf(BOLD_GREEN "Game saved succesfully at %s\n" COLOR_RESET, new_save->data.date_time);
}

SaveNode* get_save_list(GameData *data) {
    return data->save_list_head;
}

bool delete_save(GameData *data, int index) {
    if (index < 1 || data->save_list_head == NULL){
        return false;
    }

    SaveNode *current = data->save_list_head;
    SaveNode *prev = NULL;
    int count = 1;

    /*find the node to delete*/
    while(current != NULL && count < index){
        prev = current;
        current = current->next;
        count++;
    }

    if(current == NULL){
        return false; // index out of the bounds
    }

    /*remove from the linked list*/
    if(prev == NULL){
        data->save_list_head = current->next; // removing head
    }else{
        prev->next = current->next;
    }
    
    /*free memory*/
    free(current);
    return true;
}

bool load_save(GameData *data, int index) {
    SaveNode *current = data->save_list_head;
    int count = 1;
    
    // Find save by index
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }
    
    if (current == NULL) {
        return false;
    }

    /*restore the data from the snapshot to the active game*/
    data->current_hero = current->data.hero_snapshot;
    
    for(int i = 0; i < MAX_MISSIONS; i++){
        data->missions[i] = current->data.mission_snapshot[i];
    }
    
    return true;
}