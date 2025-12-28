/**
 * @file save_manager.c
 * @author Otajon 908553
 * @brief Save/load game state using linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "save_manager.h"
#include "game_data.h" 
#include "../../include/game_types.h"


/* Helper: Get current date/time */
static void get_current_datetime(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%d-%m-%Y %H:%M:%S", t);
}

/* Helper: Find save node by index (1-based) */
static SaveNode* get_save_at_index(SaveNode *head, int index) {
    SaveNode *current = head;
    int count = 1;
    
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }
    return current;
}

void save_game(GameData *data) {
    /* Create new save node */
    SaveNode *new_save = (SaveNode*)malloc(sizeof(SaveNode));
    if (new_save == NULL) {
        printf("Error: Cannot allocate memory for save!\n");
        return;
    }
    
    /* Get current date/time */
    get_current_datetime(new_save->data.data_time, MAX_STRING_LEN);
    
    /* Use Fernando's function to create save data */
    new_save->data = create_save_data(data);
    
    /* Add to front of linked list */
    new_save->next = data->save_list_head;
    data->save_list_head = new_save;
    
    printf("Game saved successfully at %s\n", new_save->data.data_time);
}

SaveNode* get_save_list(GameData *data) {
    return data->save_list_head;
}

bool delete_save(GameData *data, int index) {
    if (index < 1) return false;
    
    SaveNode *current = data->save_list_head;
    SaveNode *prev = NULL;
    int count = 1;
    
    /* Find the node to delete */
    while (current != NULL && count < index) {
        prev = current;
        current = current->next;
        count++;
    }
    
    if (current == NULL) {
        return false;  /* Index out of bounds */
    }
    
    /* Remove from linked list */
    if (prev == NULL) {
        data->save_list_head = current->next;  /* Removing head */
    } else {
        prev->next = current->next;
    }
    
    /* Free memory */
    free(current);
    return true;
}

bool load_save(GameData *data, int index) {
    SaveNode *save = get_save_at_index(data->save_list_head, index);
    
    if (save == NULL) {
        return false;
    }
    
    /* Use Fernando's function to load game data */
    load_game_data(data, &save->data);
    
    return true;
}


