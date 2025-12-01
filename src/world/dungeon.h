#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>
#include "../entities/player.h"   //This is for the player structure

//All mission types
typedef enum{
    MISSION_ROTTING_SWAMP = 1,
    MISSION_HAUNTED_MANSION = 2,
    MISSION_CRYSTAL_CAVE = 3,
    MISSION_DARK_LORD_CASTLE = 4
} MissionType;

//All room types
typedef enum{
    ROOM_EMPTY,
    ROOM_TRAP,
    ROOM_ENEMY,
    ROOM_SHOP
} RoomType;

typedef struct Room Room;
typedef struct Dungeon Dungeon;

//The creation of the dungeon and its management
Dungeon* create_dungeon(int mission_type);
Room* get_current_room(Dungeon* dungeon);
void move_to_the_next_room(Dungeon* dungeon);
bool dungeon_is_complete(Dungeon* dungeon);
void free_dungeon(Dungeon* dungeon);

//The information of the room
RoomType room_get_type(const Room* room);
bool room_is_completed(const Room* room);
void room_mark_completed(Room* room);

#endif