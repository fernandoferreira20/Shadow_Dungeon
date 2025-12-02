#ifndef GAME_DATA_H
#define GAME_DATA_H

// this enum defines the possible types for a room
typedef enum {
    ROOM_TYPE_FIGHT,
    ROOM_TYPE_TRAP,
    ROOM_TYPE_EMPTY
}RoomType;

// this struct holds the definition for a single room
typedef struct RoomDefinition {
    const char* name; // e.g., "Wild Dog", "Poisonous Bog"
    RoomType type; // FIGHT, TRAP, or EMPTY
    int fatal_strike; // the base fatal strike value
    int damage; // the base "damage" value
    int coins; // the base "coins" reward
} RoomDefinition;

// --- Dungeon Room Definitions ---

// gets the room definition for the Rotting Swamp
// dice_roll The result of the d6 roll (1-6).
const RoomDefinition* get_rotting_swamp_room(int dice_roll);

// gets the room definition for the Haunted Mansion
// dice_roll The result of the d6 roll (1-6).
const RoomDefinition* get_haunted_mansion_room(int dice_roll);

// gets the room definition for the Crystal Cave
// dice_roll The result of the d6 roll (1-6).
const RoomDefinition* get_crystal_cave_room(int dice_roll);

#endif