#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include "../../include/game_types.h"

/**
 * @file save_manager.h
 * @brief Manages the creation, retrieval, and deletion of game saves
 */

/**
 * @brief Creates a new save snapshot from the current game state 
 * * Adds a new node to the global save list
 * Captures: Date/Time, Life, Coins, Items, Missions
 * @param data Pointer to the GameData structure
 */
void save_game(GameData *data);

/**
 * @brief Retrieves the head of the save list
 * @param data Pointer to the GameData structure
 * @return Pointer to the first save node (or NULL if empty)
 */
SaveNode* get_save_list(GameData *data);

/**
 * @brief Deletes a specific save from the list
 * @param data Pointer to the GameData structure
 * @param index The 1-based index of the save to delete (as shown in the menu)
 * @return true if deteltion was successful, false otherwise
 */
bool delete_save(GameData *data, int index);

/**
 * @brief Loads a specific save state into the active game data
 * @param data Pointer to the GameData structure
 * @param index The 1-based index of the save to load
 * @return true if load was successful, false otherwise
 */
bool load_save(GameData *data, int index);

#endif