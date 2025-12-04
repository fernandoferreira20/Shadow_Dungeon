#ifndef SHOP_H
#define SHOP_H

#include "../../include/game_types.h"

/**
 * @file shop.h
 * @brief Manages the in-game shop
 */

/**
 * @brief Displays the Shop Menu and handles purchases
 * * Items available:
 * - Health potion (4 coins)
 * - Sword (5 coins, +1 Attack, one-time buy)
 * - Armor (10 coins, -1 Damage, one-time buy)
 * @param hero Pointer to the Hero structure
 */
void display_shop_menu(Hero *hero);

/**
 * @brief Processes the purchase of a specific item
 * * Logic behind this process
 * 1. Checks if the player has enough coins and if the item is already owned
 * 2. Deducts coins and updated the inventory if they process is successful
 * @param hero Pointer to the Hero structure
 * @param item The type of item to purchase
 */
void purschase_item(Hero *hero, ItemType item);

#endif