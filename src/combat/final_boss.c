#include "final_boss.h"
#include "../utils/random.h"
#include "../utils/input.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MOVE_SHIELD = 1, //Rock
    MOVE_MAGIC = 2, //Paper
    MOVE_SWORD = 3 //Scissors
} BattleMove;

BattleMove get_dark_lord_move(){
    return (BattleMove)(rand() % 3 + 1);
}

const char* move_to_string(BattleMove move){
    switch(move){
        case MOVE_SHIELD: return "Shield";
        case MOVE_MAGIC: return "Magic";
        case MOVE_SWORD: return "Sword";
        default: return "Unknown";
    }
}

int determine_round_wiiner(BattleMove move_hero, BattleMove dark_lord_move){
    if(hero_move == dark_lord_move){
        return 0; //in case is a tie
    }

    if((hero_move == MOVE_SHIELD && dark_lord_move == MOVE_SWORD) || 
        (hero_move == MOVE_SWORD && dark_lord_move == MOVE_MAGIC) || 
        (hero_move == MOVE_MAGIC && dark_lord_move == MOVE_SHIELD)){
            return 1; //hero wins
    }
    return -1; //dark lord wins
}

bool final_boss_battle(Player *player){
    printf("\n=== FINAL BATTLE: THE MISTERIOUS DARK LORD ===\n");
    printf("The fate of the world rests on this battle!\n");
    printf("Rock-Paper-Scissors style combat begins!\n\n");

    int hero_score = 0;
    int dark_lord_score = 0;
    int round = 1;

    while (round <= 5 && hero_score < 3 && dark_lord_score < 3){
        printf("--- Round %d of 5 ---\n", round);
        printf("Hero: %d - Dark Lord: %d\n\n", hero_score, dark_lord_score);

        printf("Chose your move:\n");
        printf("1. Shield (Rock)\n");
        printf("2. Magic (Paper)\n");
        printf("3. Sword (Scissors)\n");

        BattleMove hero_move = (BattleMove)get_valid_input(1, 3);
        BattleMove dark_lord_move = get_darl_lord_move();

        printf("\nYou chose: %s\n", move_to_string(hero_move));
        printf("Dark Lord chose: %s\n", move_to_string(dark_lord_move));

        int result = determine_round_winner(hero_move, dark_lord_move);

        if(result == 1){
            printf("You win this round!\n");
            hero_score++;
        } else if(result == -1){
            printf("Dark Lord wins this round!\n");
            dark_lord_score++;
        } else {
            printf("It's a tie! Round continues...\n");
        }

        round++;
        printf("\n");
    }

    if(hero_score >= 3){
        printf("VICTORY! You have defetead the mighty Dark Lord!\n");
        printf("\nCONGRATULATION!\n");
        return true;
    } else {
        printf("DEFEAT! The Dark Lord has prevailed...\n");
        return false;
    }
}