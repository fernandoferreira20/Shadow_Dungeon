/**
 * @file mission_menu.c
 * @author Alexandru 907625
 * @brief Procedural dungeon generation and room logic
 */

 #include <stdio.h>
 #include <string.h>
 #include "dungeon.h"
 #include "../../utils/random.h"
 #include "../../comabt/combat.h"

 static void setup_room(Dungeon *room, MissionType m_type, int roll){
    room->is_cleared = false;
    room->type = ROOM_FIGHT;

    if(m_type == MISSION_SWAMP){
        if(roll == 1) room->content = create_enemy(WILD_DOG);
        else if (roll == 2) room->content = create_enemy(GOBLIN);
        else if (roll == 3) room->content = create_enemy(SKELETON);
        else if (roll == 4) room->content = create_enemy(ORC);
        else if (roll == 5) { room->type = ROOM_TRAP; strcpy(room->content.name, "Poisonous Bog"); room->content.damage_inflicted = 3; }
        else if (roll == 6) room->content = create_enemy(ORC_GENERAL);
    } else if(m_type == MISSION_MANSION){
        if (roll == 1) { 
            room->type = ROOM_TRAP; 
            strcpy(room->content.name, "Dark Hatch"); 
            room->content.damage_inflicted = 3; 
        }
        else if (roll == 2) room->content = create_enemy(BAT);
        else if (roll == 3) room->content = create_enemy(ZOMBIE);
        else if (roll == 4) room->content = create_enemy(PHANTOM);
        else if (roll == 5) room->content = create_enemy(GREATER_VAMPIRE);
        else if (roll == 6) room->content = create_enemy(GUARDIAN_DEMON);
    } else if (m_type == MISSION_CAVE) {
        if (roll == 1) room->type = ROOM_EMPTY;
        else if (roll == 2) {
            room->type = ROOM_TRAP; 
            strcpy(room->content.name, "Falling Crystals"); 
            room->content.damage_inflicted = 2; 
        }
        else if (roll == 3) { 
            room->type = ROOM_TRAP; 
            strcpy(room->content.name, "Unsafe Bridge"); 
            room->content.fatal_strike_req = 999; 
            room->content.coins_reward = 2; 
            room->content.damage_inflicted = 2; 
        }
        else if (roll == 4) { 
            room->type = ROOM_TRAP; 
            strcpy(room->content.name, "Mysterious Chest"); 
            room->content.damage_inflicted = 3; 
        }
        else if (roll == 5) { 
            room->type = ROOM_TRAP; 
            strcpy(room->content.name, "Steep Cliff"); 
            room->content.damage_inflicted = 3; 
        }
        else if (roll == 6) room->content = create_enemy(ANCIENT_DRAGON);
    }
 }

 Dungeon create_dungeon(MissionType type){
    Dungeon d;
    d.mission_type = type;
    d.current_room_index = 0;

    printf("\nGenerating Dungeon (Type: %d)...\n", type);
    for(int i = 0; i < MAX_DUNGEON_ROOMS; i++){
        setup_room(&d.rooms[i], type, roll_die());
    }

    for(int i = FORCED_MISSION_ROOM - 1; i < MAX_DUNGEON_ROOMS; i++){
        if(type == MISSION_SWAMP){
            d.rooms[i].type = ROOM_FIGHT;
            d.rooms[i].content = create_enemy(ORC_GENERAL);
        }
    }
    return d;
 }

 void process_current_room(Dungeon *dungeon, Hero *hero, MissionStatus *status){
    if(dungeon->current_room_index >= MAX_DUNGEON_ROOMS) return;

    DungeonRoom *room = &dungeon->rooms[dungeon->current_room_index];
    printf("\n--- Room %d ---\n", dungeon->current_room_index + 1);

    if(room->type == ROOM_EMPTY) printf("Empty Room.\n");
    else if(room->type == ROOM_TRAP) apply_trap_effect(hero, &room->content);
    else if(room->type == ROOM_FIGHT) fight_enemy(hero, &room->content, status);

    dungeon->current_room_index++;
 }