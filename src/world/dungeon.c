#include "dungeon.h"
#include "../assets/game_data.h"
#include "../utils/random.h"
#include <stdlib.h>
#include <stdio.h>

Dungeon* generate_dungeon(mission_type){
    Dungeon *dungeon = malloc(sizeof(Dungeon));
    dungeon->mission_type = mission_type;
    dungeon->current_room = 0;
    dungeon->total_rooms = 0;

    dungeon->rooms = NULL;

    return dungeon;
}

Room* generate_room(int mission_type, int room_number){
    Room *room = malloc(sizeof(Room));
    int dice_roll = roll_dice();

    switch (mission_type){
        case MISSION_ROTTING_SWAMP:
            room = get_rotting_swamp_room(dice_roll);
            break;

        case MISSION_HAUNTED_MANSION:
            room = get_haunted_mansion_room(dice_roll);
            break;

        case MISSION_CRYSTAL_CAVE:
            room = get_crystal_cave_room(dice_roll);
            break;
        
        default:
            room->type = ROOM_EMPTY;
            break;
    } 

    room->completed = false;
    return room:
}

Room* get_current_room(Dungeon *dungeon){
    if(dungeon->current_room < dungeon->total_rooms){
        return &dungeon->rooms[dungeon->current_room];
    }
    return NULL;
}

bool move_to_the_next_room(Dungeon *dungeon){
    if(dungeon->current_room < dungeon->total_rooms - 1){
        dungeon->current_room++;
        return true;
    }
    return false;
}

void free_dungeon(Dungeon *dungeon){
    if(dungeon->rooms){
        free(dungeon->rooms);
    }
    free(dungeon);
}