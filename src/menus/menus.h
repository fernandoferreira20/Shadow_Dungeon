#ifndef MENUS_H
#define MENUS_H

/**
 * @file menus.h
 * @brief General helper function for menu formatting and display
 */

/** @brief Clear the console screen */
void clear_screen();

/** @brief Prints a horizontal divider for visual separation */
void print_divider();

/** 
 * @brief Prints a standard header title for a menu
 * @param title The string to display as a header
 */
void print_header(const char *title);
 
#endif