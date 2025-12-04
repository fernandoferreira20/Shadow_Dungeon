#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "../../include/game_types.h"

/**
 * @file game_data.h
 * @brief Utilities to manage the central GameData structure
 */

/**
 * @brief Populates the active GameData from a SaveData snapshot
 * * Used when the player selects "Load Game". Copies stats, inventory,
 * and mission progress from the save file into the current game state
 * @param data Pointer to the active GameData to populate
 * @param save Pointer to the source SaveData
 */
void load_game_data(GameData *data, const SaveData *save);

/**
 * @brief Creates a SaveData snapshot from the current game state
 * * This is used when the player wants to save the game
 * @param data Pointer to the GameData
 * @return A struct containing the persistent state
 */
SaveData create_save_data(const GameData *data);

#endif