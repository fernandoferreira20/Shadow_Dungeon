#ifndef INVENTORY_H
#define INVENTORY_H

#include "../../include/game_types.h"

/**
 * @file inventory.h
 * @brief Functions for viewing and managing the hero's inventory
 */

/**
 * @brief Displays the Hero's current status
 * * Shows:
 * - Life Points
 * - Coins
 * - Possessed Items (Sword, Armor, etc)
 * - Potions Count
 * @param hero Pointer to the Hero structure
 */
void display_inventory(const Hero *hero);

/**
 * @brief Using the health potion
 * * Logic:
 * 1. Checks if hero has potions
 * 2. If yes, roll the die (1-6)
 * 3. Restore that amount of health (up to MAX_LIFE)
 * 4. Decrement potion count
 * @param hero Pointer to the Hero structure
 */
void use_health_potion(Hero *hero);

#endif