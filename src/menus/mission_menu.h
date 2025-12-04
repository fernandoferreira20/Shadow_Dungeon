#ifndef MISSION_MENU_H
#define MISSION_MENU_H

#include "../../include/game_types.h"
#include "../world/dungeon.h"

/**
 * @file mission_menu.h
 * @brief Handles the in-game menu for missions
 */

/**
 * @brief Displays the mission menu and handles user input
 * * Options: 
 * 1. Explore Dungeon Room
 * 2. Shop
 * 3. Inventory
 * 4. Return to village
 * @param hero Pointer to hero
 * @param dungeon Pointer to the dungeon
 * @param status Pointer to the mission status
 */
void display_mission_menu(Hero *hero, Dungeon *dungeon, MissionStatus *status);

/**
 * @brief Attempting to exit the mission without completing it 
 * * Conditions:
 * 1. If Mission is Complete -> Returns true (Free)
 * 2. If Mission Incomplete -> Checks for 50 Coins
 * - If rich enough: Deducts 50 coins, Returns true
 * - If poor: Prints error, Returns false
 * @param hero Pointer to hero
 * @param status Pointer to the mission status
 * @return true if exit is allowed, false otherwise
 */
bool return_to_village(Hero *hero, const MissionStatus *status);

#endif