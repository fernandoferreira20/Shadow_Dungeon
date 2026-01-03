#ifndef VILLAGE_H
#define VILLAGE_H

#include "game_types.h"

/**
 * @file village.h
 * @brief Manages the Main Village and hub interactions
 */

/**
 * @brief Display the Village Menu
 * @param data Pointer to GameData structure
 */
void display_village_menu(const GameData *data);

/**
 * @brief Restore Hero's life points (to MAX_LIFE)
 * @param hero Pointer to the hero to heal
 */
void rest_in_village(Hero *hero);

/**
 * @brief Handling the logic to exit the game
 * @param data Pointer to GameData structure
 */
void perform_exit_sequence(GameData *data);

/**
 * @brief Main Loop of the Village
 * * Handles user input to choose between Missions, Rest, Inventory, Save or Exit
 * @param data Pointer to GameData structure
 * @return int: The Mission ID selected (0-3), or -1 to Exit Game
 */
int enter_village(GameData *data);

#endif