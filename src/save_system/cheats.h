#ifndef CHEATS_H
#define CHEATS_H

#include "game_types.h"

/**
 * @file cheats.c
 * @brief Manages hidden cheat functionality and the Konami code state
 */

/**
 * @brief Check a character input against the Konami Code sequence
 * * Sequence: w, w, s, s, a, d, a, d, b, a, [Space]
 * * Updates the state machine. If the full code is entered, sets data->cheats_unlocked to true
 * @param data Pointer to the GameData structure
 * @param input The character input from the user
 */
void check_konami_code(GameData *data, char input);

/**
 * @brief Displays the Cheat Menu
 * * Allow the user to:
 * 1. Modify Hero Statistics (Life, Coins)
 * 2. Unlock the Final Mission immediately
 * @param data Pointer to the GameData structure
 */
void display_cheats_menu(GameData *data);

#endif