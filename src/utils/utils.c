/**
* @file utils.c
* @author Fernado 908697
* @brief Implementation of general utility functions for valid inputs.
*/

#include "utils.h"
#include <stdio.h>

void clear_input_buffer(){
    int c;
    // Standard C idiom: read chapters till newline or end of file
    // This is safer than scanf("%c")
    while((c = getchar()) != '\n' && c != EOF);
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
        }else if(value < min || value > max){
            printf("Please enter a value between %d and %d.\n", min, max);
            // We clear buffer here too. If user typed "5 abc", we want to consume "abc"
            // so the next loop doesn't fail immediately.
            clear_input_buffer();
        }else{
            // the input is valid
            clear_input_buffer(); // clean up the "Enter" key that is still sitting in the buffer
            return value;
        }
    }
}

void press_enter_to_continue(){
    printf("\nPress [Enter] to continue.....");
    // Since the buffer is empty (from previous inputs), 
    // this will wait for the user to type the next newline.
    clear_input_buffer();
}