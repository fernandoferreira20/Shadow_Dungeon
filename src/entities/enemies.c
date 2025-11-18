#include "enemies.h"
#include <stddef.h> // For NULL

// --- Helper Function ---

// Recursive function to calculate the Nth Padovan number
// P(n) = P(n-2) + P(n-3)
// Base cases: P(0)=1, P(1)=1, P(2)=1
static int calculate_padovan_recursive(int n){
    if(n <= 2){
        return 1;
    }
    return calculate_padovan_recursive(n - 2) + calculate_padovan_recursive(n - 3);
}

// --- Public Functions ---

int is_enemy(const RoomDefinition* room){
    if(room == NULL){
        return 0;
    }
    // it is an enemy if the type is a FIGHT
    return (room->type == ROOM_TYPE_FIGHT);
}

int is_padovan_number(int number){
    if(number < 1) return 0; // Padovan numbers are positive

    // We generate numbers recursively untill we find the number
    // or exceed it
    int n = 0;
    int p_n = 0;
    
    while(1){
        p_n = calculate_padovan_recursive(n);

        if(p_n == number){
            return 1; // found it
        }
        if(p_n > number){
            return 0; // eceeded it, so it is not in the sequence
        }
        n++;
    }
}