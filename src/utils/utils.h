#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @brief General utility functions for input validation and handling the strings
 */

/** 
  * @brief Requesting an integer as in input from the user
  * @param prompt The message to display to the user
  * @param min The minimum acceptable value
  * @param max The maximum acceptable value 
  * @return The validated integer entered by the user
  */
    
int get_int_input(const char *prompt, int min, int max);

/** @brief Clears the input buffer */
void clear_input_buffer();

/** @brief Pauses the execution until the user presses enter */
void press_enter_to_continue();

#endif