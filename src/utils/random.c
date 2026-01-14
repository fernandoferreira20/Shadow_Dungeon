/**
* @file random.c
* @author Fernado 908697
* @brief Implementation of random number generation utilities using standard C libraries.
*/

#include "random.h"
#include <stdlib.h> // for rand() and srand()
#include <time.h> // for time

void seed_random(){
    // use the current time as the seed for the random number generator
    srand((unsigned int)time(NULL));
}

int roll_die(){
    // returns a number between 1 and 6
    return rand() % 6 + 1;
}

int flip_coin(){
    // return 0 and 1
    return rand() % 2;
}

int get_random_in_range(int min, int max){
    if(min > max){
        // fallback if inputs are swapped
        int temp = min;
        min = max;
        max = temp;
    }
    // Calculate the range size and offset by min
    return min + (rand() % (max - min + 1));
}