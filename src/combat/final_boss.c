/**
 * @file final_boss.c
 * @brief Implementation of the Dark Lord fight and Padovan Sequence
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "final_boss.h"
 #include "utils/random.h"
 #include "utils/utils.h"
 #include "game_constants.h"

 // --- Padovan Sequence Logic ---
 // Sequence: 1, 1, 1, 2, 2, 3, 4, 5, 7, 9, 12...
 static int padovan_recursive(int n){
    if(n == 0 || n == 1 || n == 2) return 1;
    // P(n) = P(n-2) + P(n-3)
    return padovan_recursive(n - 2) + padovan_recursive(n - 3);
 }

 int is_padovan(int number){
    if(number < 1) return 0;
    int n = 0;
    int val = 0;
    
    // Check terms until we find the number or surpass it
    while(1) {
        val = padovan_recursive(n);
        if(val == number) return 1; // Found it
        if(val > number) return 0;  // Passed it, so it's not in sequence
        n++;
    }
 }

 // --- Boss Fight Logic ---
 int resolve_round(BossMove hero_move, BossMove boss_move){
    if(hero_move == boss_move) return 0; // Draw
    
    // Rock (Shield) vs Scissors (Sword) -> Rock wins
    // Scissors (Sword) vs Paper (Magic) -> Scissors wins
    // Paper (Magic) vs Rock (Shield) -> Paper wins
    if((hero_move == MOVE_SHIELD && boss_move == MOVE_SWORD) || 
       (hero_move == MOVE_SWORD && boss_move == MOVE_MAGIC) ||
       (hero_move == MOVE_MAGIC && boss_move == MOVE_SHIELD)) {
        return 1; // Hero wins
    }
    return -1; // Boss wins
 }

 void final_boss_fight(Hero *hero){
    printf("\n=== FINAL BATTLE: THE DARK LORD ===\n");
    printf("Win %d out of %d rounds to save the world!\n", BOSS_WINS_NEEDED, BOSS_TOTAL_ROUNDS);

    int hero_wins = 0, dark_lord_wins = 0, rounds = 0;

    // Loop until one side wins enough rounds OR we run out of rounds
    while (rounds < BOSS_TOTAL_ROUNDS && hero_wins < BOSS_WINS_NEEDED && dark_lord_wins < BOSS_WINS_NEEDED) {
        printf("\n--- ROUND %d ---\n1. Shield\n2. Magic\n3. Sword\n", rounds + 1);
        
        // Use standard input utility
        int input = get_int_input("Choose your move: ", 1, 3);
        BossMove hero_move = (BossMove)input;
        BossMove boss_move = (BossMove)get_random_in_range(1, 3);

        const char *moves[] = {"", "Shield", "Magic", "Sword"};
        printf("You: %s | Dark Lord: %s\n", moves[hero_move], moves[boss_move]);

        int result = resolve_round(hero_move, boss_move);
        if(result == 1) {
            printf(">> You WIN this round!\n");
            hero_wins++;
        } else if (result == -1){
            printf(">> Dark Lord WINS this round!\n");
            dark_lord_wins++;
        } else {
            printf(">> DRAW! Replaying round...\n");
            continue; // Don't increment round counter on draw
        }
        rounds++;
        press_enter_to_continue();
    }

    if(hero_wins >= BOSS_WINS_NEEDED){
        printf("\n*** CONGRATULATIONS! YOU DEFEATED THE DARK LORD! ***\n");
        press_enter_to_continue();
    } else {
        printf("\nYou have been defeated... Darkness consumes the world.\n");
        hero->life_points = 0;
        press_enter_to_continue();
    }
 }