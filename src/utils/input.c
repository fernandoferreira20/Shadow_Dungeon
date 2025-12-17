/**
* @file input.c
* @author Fernado 908697
* @brief Implementation of simple input handling using standard C functions.
*/

#include "input.h"
#include <stdio.h>

char read_single_char(){
    char c;

    scanf(" %c", &c);
    return c;
}