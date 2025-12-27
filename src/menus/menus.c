/**
 * @file menu.c
 * @author Otajon 908553
 * @brief implementation of menu, building helper functions
 */

#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void print_divider() {
    printf("----------------------------------------\n");
}

void print_header(const char *title) {
    printf("\n=== %s ===\n", title);
}