/**
 * @file main.c
 * @author Harshit 908571
 * @brief Entry point of the RPG Project
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "game_engine.h"
 #include "../include/game_types.h"

 int main(void){
    GameData game_data;
    run_game_loop(&game_data);

    return 0;
 }