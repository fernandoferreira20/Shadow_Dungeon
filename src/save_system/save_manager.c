 /**
 * @file save_manager.c
 * @author Otajon 908553
 * @brief Save/load game state using linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "save_manager.h"
#include "game_data.h" // Needed for create_save_data/load_game_data
#include "game_types.h"

void save_game(GameData *data) {
    /* Create new save node */
    SaveNode *new_save = (SaveNode*)malloc(sizeof(SaveNode));
    if (new_save == NULL) {
        printf("Error: Cannot allocate memory for save!\n");
        return;
    }
    
    /* Create the save snapshot (Timestamp is handled inside create_save_data) */
    new_save->data = create_save_data(data);
    
    /* Add to front of linked list */
    new_save->next = data->save_list_head;
    data->save_list_head = new_save;
    
    printf("Game saved successfully at %s\n", new_save->data.date_time);
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
    
    /* Load the data */
    load_game_data(data, &current->data);
    
    return true;
}