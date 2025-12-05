#ifndef RANDOM_H
#define RANDOM_H

/**
 * @file random.h
 * @brief Functions for random number generation
 */

/** @brief Initializes the random number generation with a time-based seed */
void seed_random();

/** 
 * @brief Simulates rolling a 6-sided die
 * @return A random number between 1 to 6
 */
int roll_die();

/**
 * @brief Simulates flipping a coin
 * @return 1 for Head and 0 for Tails
 */
int flip_coin();

/** 
 * @brief Generates a random number within a custom range
 * @param min Lower bound
 * @param max Upper bound
 * @return Random integer between min and max
 */
int get_random_in_range(int min, int max);

#endif
