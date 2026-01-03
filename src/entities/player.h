#ifndef PLAYER_H
#define PLAYER_H

#include "game_types.h"

/**
 * @file player.h
 * @brief Functions for managing the Hero
 */

/**
 * @brief Creates a new Hero with starting stats
 * * Default: 20 Life Points, 0 Coins, 0 Items
 * @return A capitalized Hero structure
 */
Hero create_hero();

/**
 * @brief Updates the Hero's stats
 * We make sure that the Life Points don't go below 0 and above 20
 * Handling adding/removing coins
 * @param hero Pointer to the Hero structure
 * @param life_delta Change in life points (+ to heal, - to damage)
 * @param coin_delta Change in coins (+ to add, - to remove)
 */
void update_hero_stats(Hero *hero, int life_delta, int coin_delta);

/**
 * @brief Checks if the Hero has been defeated
 * @param hero Pointer to the Hero structure
 * @return true if life_points <= 0, false otherwise
 */
bool is_hero_dead(const Hero *hero);

#endif