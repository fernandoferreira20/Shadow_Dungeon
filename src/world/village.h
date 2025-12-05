#ifndef VILLAGE_H
#define VILLAGE_H

#include "../../include/game_types.h"

/**
 * @file village.h
 * @brief Manages the Main Village and hub interactions
 */

/**
 * @brief Display the Village Menu
 * * Options:
 * 1. Start a mission
 * 2. Rest (Restore life)
 * 3. Inventory
 * 4. Save Game
 * 5. Exit
 * @param data Poiner to GameData structure
 */
void display_village_menu(GameData *data);

/**
 * @brief Restore Hero's life points (to MAX_LIFE 20)
 * @param hero Pointer to the hero to heal
 */
void rest_in_village(Hero *hero);

/**
 * @brief Handling the logic to exit the game
 * * Display a warning message such as "Remember to save the game" before closing
 * @param data Pointer to GameData structure
 */
void perform_exit_sequence(GameData *data);

#endif