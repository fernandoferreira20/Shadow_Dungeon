#ifndef GAME_ENGINE.H
#define GAME_ENGINE.H

#include "../include/game_types.h" // we need this because it contains important functions

/** 
 * @file game_engine.h
 * @brief Core game loop and initialization logic
 */

/** 
  * @brief Initialize a new game
  * * Sets hero to 20 life points, 0 coins, resets missions, and prepares the game data
  * @param data Pointer to the main GameData structure
  */
void initialize_game(GameData *data); // we call this function from game_types header

/** 
 * @brief The main execution of the game loop
 * * Handles the transition between the Village, Missions and Menus
 * @param data Pointer to the active GamaData structure
 */
void run_game_loop(GameData *data);

#endif