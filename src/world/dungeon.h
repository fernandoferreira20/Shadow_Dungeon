#ifndef DUNGEON_H
#define DUNGEON_H

#include "../../include/game_types.h"
#include "../entities/enemies.h"

/**
 * @file dungeon.h
 * @brief Handles the dungeon generation and room managment
 */

/** @brief Represents the content of a single dungeon room */
typedef enum {
    ROOM_EMPTY,
    ROOM_TRAP,
    ROOM_FIGHT
} RoomType;

/** @brief Defines a single room within the dungeon */
typedef struct DungeonRoom{
    RoomType type;
    /** @brief Contains the enemy data for fights or trap data for traps */
    Enemy content;
    bool is_cleared; //true if the room has been cleared from enemies
} DungeonRoom;

/** @brief Represents the entire active dungeon */
typedef struct Dungeon {
    DungeonRoom rooms[MAX_DUNGEON_ROOMS];
    int current_room_index; //this is to track the player progress
    MissionType mission_type;
} Dungeon;

/**
 * @brief Generates a new procedural dungeon
 * * Algorithm:
 * 1. Iterates from 0 to MAX_DUNGEON_ROOMS
 * 2. Rolls a die for each room based on the Mission Table
 * 3. Forces Mission Goals if they haven't appeared by room 7
 * @param type The mission type
 * @return A fully populated dungeon structure
 */
Dungeon create_dungeon(MissionType type);

/**
 * @brief Procces the logic for the current room
 * * If there is a ROOM_FIGHT call the combat system
 * * If there is a ROOM_TRAP applies the trap damage
 * * If there is a ROOM_EMPTY prints message
 * @param dungeon Pointer to the active dungeon
 * @param hero Pointer to the hero
 * @param status Pointer to the MissionStatus
 */
void process_current_room(Dungeon *dungeon, Hero *hero, MissionStatus *status);

#endif