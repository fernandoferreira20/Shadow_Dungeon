/**
* @file utils.c
* @author Fernado 908697
* @brief Implementation of general utility functions for valid inputs.
*/

#include "utils.h"
#include <stdio.h>

void clear_input_buffer(){
    char c = ' '; // temporary variable

    // keep scaning one chapter at a time until we find the "Enter" key
    while(c != '\n'){
        scanf("%c", &c);
    }
}

int get_int_input(const char *prompt, int min, int max){
    int value;
    int result;

    while(1){
        printf("%s", prompt);
        result = scanf("%d", &value);

        if(result == 0){
            // if scanf returns 0, it means the user typed a letter instead of a number
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer(); // clear the bad letters
        }else if(value < min){
            printf("Please enter a value between %d and %d.\n", min, max);
            // no need to clear buffer here, the number was read corrctly but it was just too small
        }else if(value > max){
            printf("Please enter a value between %d and %d.\n", min, max);
        }else{
            // the input is valid
            clear_input_buffer(); // clean up the "Enter" key that is still sitting in the buffer
            return value;
        }
    }
}

void press_enter_to_continue(){
    printf("\nPress [Enter] to continue.....");
    clear_input_buffer();
}