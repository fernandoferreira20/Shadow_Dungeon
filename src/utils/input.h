#ifndef INPUT_H
#define INPUT_H

/**
 * @file input.h
 * @brief Low-level input handling for character detection.
 */

/**
 * @brief Reads a single character from stdin without requiring Enter (if possible) 
 * * Used primarily for detecting the Konami Code sequence.
 *  @return The character entered by the user.
 */
char read_single_char();

#endif