#include "village.h" // include our header file
#include <stdio.h> // for printing messages

// the maximum life points the hero life can have
#define MAX_LIFE_POINTS 20

// restores the hero's life points to the maximum (20).
void rest_hero(Hero* hero){
    if(hero == NULL){
        return; // save check
    }

    // only rest if the hero is not already at full health
    if(hero->life_points < MAX_LIFE_POINTS){
        hero->life_points = MAX_LIFE_POINTS;
        printf("\nYou rest at the village. Your life points are fully restored!\n");
    }else{
        printf("\nYou are already at full health.\n");
    }

}


// real