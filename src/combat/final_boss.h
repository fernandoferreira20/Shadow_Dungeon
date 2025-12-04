#ifndef FINAL_BOSS_H
#define FINAL_BOSS_H

#include "../../include/game_types.h"

/**
 * @file final_boss.h
 * @brief Manages the final fight in this game
 */

/** @brief Enum for Rock-Paper-Scissors mechanics */
typedef enum {
    MOVE_SHIELD = 1, //rock
    MOVE_MAGIC = 2, //paper
    MOVE_SWORD = 3 //scissors
} BossMove;

/**
 * @brief Manages the final boss mechanics
 * * The player has to win 3 rounds out of 5
 * @param hero Pointer to hero
 */
void final_boss_fight(Hero *hero);

/**
 * @brief Determines who is the winner
 * * Rules:
 * - Shield beats Sword
 * - Sword beats Magic
 * - Magic beats Shield
 * @param hero_move The player's choice
 * @param boss_move The boss's move
 * @return 1 if Hero wins and -1 if Boss wins and 0 if is draw
 */
int resolve_round(BossMove hero_move, BossMove boss_move);

/**
 * @brief Checks if a number belongs to the padovan sequence
 * It is implemented recursively
 * Sequence: P(n) = P(n-2) + P(n-3)
 * It is used for the interaction with the ancient dragon
 * @param n The number to check
 * @return 1 (true) if the number is in the sequence, 0 (false) otherwise
 */
int is_padovan(int n);

#endif