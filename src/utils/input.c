 /**
* @file input.c
* @author Fernado 908697
* @brief Implementation of simple input handling using standard C functions.
*/

#include "input.h"
#include "utils.h" // We need utils.h to access clear_input_buffer()
#include <stdio.h>

char read_single_char(){
    char c;

    // Cast to void to silence the "unused result" warning
    if (scanf(" %c", &c)){}
    
    clear_input_buffer(); 
    return c;
}