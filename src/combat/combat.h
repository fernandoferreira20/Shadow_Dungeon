#ifndef COMBAT_H
#define COMBAT_H

#include <stdbool.h>
#include "../entities/player.h"  //This is for the player structure
#include "../entities/enemies.h"  //This is for the enemy structure

//Combat result after a fight
typedef enum{
    COMBAT_VICTORY,
    COMBAT_DEFEAT,
    COMBAT_CONTINUE
} CombatResult;

//Combat functions
CombatResult combat_encounter(Player *player, Enemy *enemy);
int calculate_hero_attack(const Player *player);
void apply_damage(Player *player, int damage);
void award_coins(Player *player, int coins);

//Padovan sequence
int padovan(int n);
bool is_in_padovan_sequence(int number);

#endif