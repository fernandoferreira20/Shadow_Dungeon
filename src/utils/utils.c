/**
* @file utils.c
* @author Fernado 908697
* @brief Implementation of general utility functions for valid inputs.
*/

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void clear_screen(){
    // Standard ANSI escape sequence to clear the screen and home the cursor
    printf("\033[H\033[J");
    
    #ifdef _WIN32
        // Fallback for Windows environments where ANSI might not be enabled
        system("cls");
    #endif
}

void clear_input_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int get_int_input(const char *prompt, int min, int max){
    int value;
    int result;

    while(1){
        // Format prompt with a visual indicator
        printf(BOLD_CYAN "> " COLOR_RESET "%s", prompt);
        result = scanf("%d", &value);

        if(result == 0){
            printf(BOLD_RED " [!] Error: Invalid input. Please enter a number.\n" COLOR_RESET);
            clear_input_buffer();
        }else if(value < min || value > max){
            printf(BOLD_RED " [!] Error: Value out of range (%d-%d).\n" COLOR_RESET, min, max);
            clear_input_buffer();
        }else{
            clear_input_buffer();
            return value;
        }
    }
}

void press_enter_to_continue(){
    // Use a distinct color to separate the pause from game text
    printf("\n" BOLD_CYAN "  Press [Enter] to continue... " COLOR_RESET);
    clear_input_buffer();
}