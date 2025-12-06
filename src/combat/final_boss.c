/**
 * @file mission_menu.c
 * @author Alexandru 907625
 * @brief Implementation of the Dark Lord fight and Padovan Sequence
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "final_boss.h"
 #include "../../utils/random.h"
 #include "../../utils/utils.h"
 #include "../../include/game_constants.h"

 // Implementing the Padovan Sequence
 static int padovan_recursive(int n){
    if(n == 0 || n == 1 || n == 2) return 1;
    return padovan_recusive(n - 2) + padovan_recursive (n - 3);
 }

 int is_padovan(int number){
    if(number < 1) return 0;
    int n = 0;
    int val = 0;
    while(1) {
        val = padovan_recursive(n);
        if(val == number) return 1;
        if(val > number) return 0;
        n++;
    }
 }

 // Implementing the final boss logic
 int resolve_round(BossMove hero_move, BossMove boss_move){
    if(hero_move == boss_move) return 0;
    if((hero_move == MOVE_SHIELD && boss_move == MOVE_SWORD) || 
       (hero_move == MOVE_SWORD && boss_move == MOVE_MAGIC) ||
       (hero_move == MOVE_MAGIC && boss_move == MOVE_SHIELD)) return 1;
    return -1;
 }

 void final_boss_fight(Hero *hero){
    printf("\n=== FINAL BATTLE: THE DARK LORD ===\n");
    printf("Win %d out of %d rounds to save the world!\n", BOSS_WINS_NEEDED, BOSS_TOTAL_ROUNDS);

    int hero_wins = 0, dark_lord_wins = 0, rounds = 0;

    while (rounds < BOSS_TOTAL_ROUNDS && hero_wins < BOSS_WINS_NEEDED && dark_lord_wins < BOSS_WINS_NEEDED) {
        printf("\n--- ROUND %d ---\n1. Shield\n2. Magic\n3. Sword\n", rounds + 1);
        int input = get_int_input("Move: ", 1, 3);
        BossMove hero_move = (BossMove)input;
        BossMove boss_move = (BossMove)get_random_in_range(1, 3):

        const char *moves[] = {"", "Shield", "Magic", "Sword"};
        printf("You: %s | Dark Lord: %s\n", moves[hero_move], moves[boss_move]);

        int result = resolve_round(hero_move, boss_move);
        if(result == 1) {
            printf("You WIN round!\n");
            hero_wins++;
        } else if (result == -1){
            printf("Dark Lord WINS round!\n");
            dark_lord_wins++;
        } else {
            printf("DRAW! Replaying round...\n");
            continue;
        }
        rounds++;
    }

    if(hero_wins >= BOSS_WINS_NEEDED){
        printf("\n*** CONGRATULATIONS! YOU DEFEATED THE DARK LORD! ***\n");
        press_enter_to_continue();
    } else {
        printf("\nYou have been defeated...\n");
        hero->life_points = 0;
    }
 }