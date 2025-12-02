#ifndef ENEMIES_H
#define ENEMIES_H

#include "../../assets/game_data.h" // To access RoomDefinition

// This helps Person 3 (Combat) know when to start a fight.
int is_enemy(const RoomDefinition* room);

// This is the special behavior for the Ancient Dragon (Crystal Cave).
// number The number to check (e.g., the random 1-500 generated).
int is_padovan_number(int number);

#endif