#include "game_data.h"  // We need our header for the struct definitions
#include <stddef.h> // for NULL

// --- Rotting Swamp Data (Table 2) ---
// This array is "static", so it is PRIVATE to this file.
// We use 'const' because this data should never change.
static const RoomDefinition ROTTING_SWAMP_ROOMS[6] = {
    // dice roll 1: "Wild Dog"
    {"Wild Dog", ROOM_TYPE_FIGHT, 2, 1, 2},

    // dice roll 2: "Goblin"
    {"Goblin", ROOM_TYPE_FIGHT, 3, 2, 4},

    // dice roll 3: "Skeleton"
    {"Skeleton", ROOM_TYPE_FIGHT, 2, 2, 3},

    // dice roll 4: "Orc"
    {"Orc", ROOM_TYPE_FIGHT, 4, 3, 6},

    // dice roll 5: "Poisonous Bog"
    {"Poisonous Bog", ROOM_TYPE_TRAP, 0, 6, 0}, // damage is 1-6, but we'll use 6 as a "max" Person 3 will have to add logic for the dice roll

    // dice roll 6: "Orc General"
    {"Orc General", ROOM_TYPE_FIGHT, 6, 3, 12}  
};

// --- Haunted Mansion Data (Table 3) ---
static const RoomDefinition HAUNTED_MANSION_ROOMS[6] = {
    {"Dark Hatch", ROOM_TYPE_TRAP, 0, 2, 0},
    {"Bat", ROOM_TYPE_FIGHT, 1, 1, 1}, // Note: Table 3 has odd stats, e.g., Fatal Strike 1 for Bat?
    {"Zombie", ROOM_TYPE_FIGHT, 2, 2, 2},
    {"Phantom", ROOM_TYPE_FIGHT, 3, 2, 4},
    {"Guardian Demon", ROOM_TYPE_FIGHT, 5, 4, 8}, // I'm guessing on stats for this one from Table 3
    {"Greater Vampire", ROOM_TYPE_FIGHT, 7, 4, 10} // I'm guessing on stats for this one from Table 3
};

// --- Crystal Cave Data (Table 4) ---
static const RoomDefinition CRYSTAL_CAVE_ROOMS[6] = {
    {"Empty Room", ROOM_TYPE_EMPTY, 0, 0, 0},
    {"Falling Crystals", ROOM_TYPE_TRAP, 0, 2, 0},
    {"Unsafe Bridge", ROOM_TYPE_TRAP, 0, 3, 0},
    {"Mysterious Chest", ROOM_TYPE_TRAP, 0, 2, 10},  // Special logic needed by Person 3
    {"Steep Cliff", ROOM_TYPE_TRAP, 0, 6, 0},       // Damage 1-6
    {"Ancient Dragon", ROOM_TYPE_FIGHT, 5, 10, 12} // Special logic needed by Person 3
};

// --- Function Definitions ---

const RoomDefinition* get_rotting_swamp_room(int dice_roll){
    if(dice_roll >= 1 && dice_roll <= 6){
        return &ROTTING_SWAMP_ROOMS[dice_roll - 1];
    }
    return NULL; // should not happen
}

const RoomDefinition* get_haunted_mansion_room(int dice_roll){
    if(dice_roll >= 1 && dice_roll <= 6){
        return &HAUNTED_MANSION_ROOMS[dice_roll - 1];
    }
    return NULL;
}

const RoomDefinition* get_crystal_cave_room(int dice_roll){
    if(dice_roll >= 1 && dice_roll <= 6){
        return &CRYSTAL_CAVE_ROOMS[dice_roll - 1];
    }
    return NULL;
}