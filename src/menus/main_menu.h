#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "game_types.h"

/**
 * @file main_menu.h
 * @brief Manages the initial Game Menu interactions
 */

/**
 * @brief Display the main game menu
 * * Handles user input
 * Note: The "cheat" is hidden until we input the konami code
 * @param data Pointer to the master GameData Structure
 */
void display_initial_menu(GameData *data);

/**
 * @brief It helps to trigger the start of a new game
 * @param data Poiner to the master GameData Structure
 */
void handle_new_game(GameData *data);

/**
 * @brief Display the "Load Game" submenu
 * * Lists available saves with their details
 * * Allow to load or delete a previous save  
 * @param data Pointer to the master GameData Structure
 */
void display_load_game_menu(GameData *data);

#endif