/**
 * @file main.c
 * @author Harshit 908571
 * @brief Entry point of the RPG Project
 */

#include <stdio.h>
#include <stdlib.h>
#include "core/game_engine.h"
#include "game_types.h"
#include "menus/main_menu.h" 

int main(void){
    // Allocate Memory
    GameData *data = (GameData*) malloc(sizeof(GameData));

    if (data == NULL) {
        printf("Fatal Error: Could not allocate memory.\n");
        return 1;
    }

    // Safe Initialization
    data->cheats_unlocked = false; 
    data->save_list_head = NULL;

    // Launch Main Menu
    display_initial_menu(data);

    // Cleanup
    free(data);
    printf("Game exited cleanly.\n");
    return 0;
}