#ifndef FINAL_BOSS_H
#define FINAL_BOSS_H

#include <stdbool.h>
#include "../entities/player.h" //This is for the player structure

//Enumerating battle moves
typedef enum {
    MOVE_SHIELD = 1, //rock
    MOVE_MAGIC = 2, //paper
    MOVE_SWORD = 3, //scissors
} BattleMove;

//Final Boss
bool final_boss_battle(Player *player);
BattleMove get_dark_lord_move();
int determine_round_winner(BattleMove hero_move, BattleMove dark_lord_move);
const char* move_to_string(BattleMove move);

#endif