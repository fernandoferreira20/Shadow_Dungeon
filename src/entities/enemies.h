#ifndef ENEMIES_H
#define ENEMIES_H

#include "../../include/game_types.h"

/**
 * @file enemies.h
 * @brief Defines enemy types and their logic
 */

/** @brief Identifiers for every enemy type in the game */
typedef enum {
    // Rotting Swamp
    WILD_DOG,
    GOBLIN,
    SKELETON,
    ORC,
    ORC_GENERAL,

    // Haunted Mansion
    BAT,
    ZOMBIE,
    PHANTOM,
    GREATER_VAMPIRE,
    GUARDIAN_DEMON,

    // Crystal Cave
    ANCIENT_DRAGON,

    // Final Boss
    DARK_LORD
} EnemyType;

/** @brief Defines the statistics and rewards for a single enemy*/
typedef struct Enemy {
    EnemyType type;
    char name[MAX_STRING_LEN];
    int fatal_strike_req; //dice roll to defeat the enemy
    int damage_inflicted; //damage dealt to hero if the attack doesn't work
    int coins_reward; //coins given to the hero in case he wins the fight
} Enemy;

/**
 * @brief Factory function to create an enemy with standard stats
 * @param type The specific type of enemy to generate
 * @return A struct containing the enemy's stats
 */
Enemy create_enemy(EnemyType type);

#endif