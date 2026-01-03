#ifndef COMBAT_H
#define COMBAT_H

#include "game_types.h"
#include "entities/enemies.h"

/**
 * @file combat.h
 * @brief Manages standard combat logic and trap interactions
 */

/**
 * @brief Calculates the hero's attack power for a single turn 
 * * Logic: Roll die + bonuses
 * * Bonues:
 * - +1 if Sword is equipped
 * - +2 if Hero Sword is equipped
 * @param hero Pointer to hero
 * @return The total attack value
 */
int hero_attack_roll(const Hero *hero);

/**
 * @brief Executes a fight loop between Hero and Enemy
 * * Logic:
 * 1. While both are alive:
 * 2. Hero attacks (calls hero_attack_roll)
 * 3. If Attack > Enemy Fatal Strike: Enemy dies, Hero gets coins
 * 4. Else: Hero takes Enemy Damage
 * 5. Updates MissionStatus if a goal enemy is defeated
 * @param hero Pointer to the hero
 * @param enemy Pointer to the enemy being fought
 * @param status Pointer to mission status (to increment kill counts)
 */
void fight_enemy(Hero *hero, Enemy *enemy, MissionStatus *status);

/**
 * @brief Applies the effect of a trap room
 * * Logic varies by trap
 * @param hero Pointer to hero
 * @param trap Pointer to the enemy
 */
void apply_trap_effect(Hero *hero, const Enemy *trap);

#endif