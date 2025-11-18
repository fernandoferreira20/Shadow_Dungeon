// It prevents the compiler from including this file more than once
#ifndef PLAYER_H
#define PLAYER_H // This 'defines' PLAYER_H, so the #ifndef check will fail next time

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this struct holds all the items the player can posses.
// we used 1 for 'true' (has the item) and 0 for 'false' (does not).
typedef struct Inventory{
    int health_potions; // Changed to health_potions (to count items)
    int has_sword; // 0 or 1. Purchased from shop
    int has_armor; // Changed from has_arrow to has_armor
    int has_castle_key; // 0 or 1. Found in Haunted Mansion
    int has_heros_sword; // 0 or 1. Found in Crystal Cave (added semicolon)
} Inventory;

// this struct holds the completion status for each mission.
// we use 1 for 'true' (complete) and 0 for 'false' (not complete).
typedef struct MissionStatus {
    int rotting_swamp;
    int haunted_mansion;
    int crystal_cave;
} MissionStatus;

// this struct holds all the data for the main player
typedef struct Hero {
    int life_points;
    int coins;
    MissionStatus missions; // nestes the struct from above inside this one
    Inventory inventory; // nestes the struct from above inside this one
} Hero;

// --- Function Prototypes for player.c ---

//  sets a hero's status to the default new game values
void initialize_new_hero(Hero* hero);

// displays the hero's currents status and inventory
void display_inventory(const Hero* hero);

// --- Function Prototypes for village.c ---

// Restores the hero's life points to the maximum (20).
void rest_hero(Hero* hero); 


#endif // This line closes the '#ifndef' block