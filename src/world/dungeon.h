#ifndef DUNGEON_H
#define DUNGEON_H

#include "../entities/player.h"

typedef enum{
    ROOM_EMPTY,
    ROOM_TRAP,
    ROOM_ENEMY,
    ROOM_SHOP
} RoomType;

typedef struct {
    RoomType type;
    int room_id;
    bool completed;
    void room_data*; //for enemy or trap data
} Room;

typedef struct {
    Room *rooms:
    int current_room;
    int total_rooms;
    int mission_type;
} Dungeon;

//Generate the dungeon
Dungeon* generate_dungeon(int mission_type);
void free_dungeon(Dungeon *dungeon);
Room* get_current_room(Dungeon *dungeon);
bool move_to_the_next_room(Dungeon *dungeon);

//Mission complete
bool check_mission_complete(Dungeon *dungeon, Player *player);

#endif