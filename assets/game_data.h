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
    const char* name; // e.g., "Wiled Dog", "Poisonous Bog"
    RoomType type; // FIGHT, TRAP, or EMPTY
    int fatal_strike; // the base fatal stric value
    int damage; // the base "damage" velue
    int coins; // the base "coins" reward
} RoomDefinition;

// --- Dungeon Room Definitions ---
// These are the "getter" functions your teammates will use.
// They get a pointer to the room data based on a dice roll (1-6).

// gets the room definition for the Rotting Swamp
// dice_roll The result of the d6 roll (1-6).
const RoomDefinition* get_rotting_swamp_room(int dice_roll);

// gets the room definition for the Haunted Mansion
// dice_roll The result of the d6 roll (1-6).
const RoomDefinition* get_hunted_mansion_room(int dice_roll);

// gets the room definition for the Crystal Cave
// dice_roll The result of the d6 roll (1-6).
const RoomDefinition* get_crystal_cave_room(int dice_roll);

#endif