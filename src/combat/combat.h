#ifndef COMBAT_H
#define COMBAT_H

#include "../entities/player.h"
#include "../entities/enemies.h"

//The result of combat
typedef enum {
    COMBAT_VICTORY,
    COMBAT_DEFEAT,
    COMBAT_CONTINUE
} CombatResult;

//Combat functions
CombatResult combat_encounter(Player *player, Enemy *enemy);
int calculate_hero_attack(const Player *player);
void apply_damage(Player *player, int damage);
void award_coins(Player *player, int coins);

#endif