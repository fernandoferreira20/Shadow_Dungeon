#ifndef MISSION_MENU_H
#define MISSION_MENU_H

#include <stdbool.h>
#include "../entities/player.h"   //This is for the player structure
#include "../world/dungeon.h" //This is for the world building 

//Mission menu functions 
void display_mission_menu(Player *player, Dungeon *dungeon);
void explore_dungeon_room(Player *player, Dungeon *dungeon);
bool return_to_village(Player *player, Dungeon *dungeon);

#endif