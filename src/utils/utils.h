#ifndef UTILS_H
#define UTILS_H

/**
* @file utils.h
* @brief General utility functions for input validation and handling strings
*/

/*---- ANSI Terminal Colors -----*/
// Standard intensity
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// High intensity / Bold
#define BOLD_WHITE    "\x1b[1;37m"
#define BOLD_RED      "\x1b[1;31m"
#define BOLD_GREEN    "\x1b[1;32m"
#define BOLD_YELLOW   "\x1b[1;33m"
#define BOLD_BLUE     "\x1b[1;34m"
#define BOLD_CYAN     "\x1b[1;36m"
#define BOLD_MAGENTA  "\x1b[1;35m"

/**
 * @brief Clears the terminal screen
 */
void clear_screen();

/** * @brief Requesting an integer as input from the user
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