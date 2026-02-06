/**
 * @file final_boss.c
 * @author Alexandru 907625
 * @brief Implementation of the Dark Lord fight and Padovan Sequence
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "final_boss.h"
 #include "utils/random.h"
 #include "utils/utils.h"
 #include "game_constants.h"
 #include "menus/menus.h" 

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
    clear_screen();
    print_header(BOLD_RED "FINAL BATTLE: THE DARK LORD" COLOR_RESET);
    printf("Win " BOLD_CYAN "%d" COLOR_RESET " out of %d rounds to save the world!\n", BOSS_WINS_NEEDED, BOSS_TOTAL_ROUNDS);
    
    press_enter_to_continue();

    int hero_wins = 0, dark_lord_wins = 0, rounds = 0;

    // Loop until one side wins enough rounds OR we run out of rounds
    while (rounds < BOSS_TOTAL_ROUNDS && hero_wins < BOSS_WINS_NEEDED && dark_lord_wins < BOSS_WINS_NEEDED) {
        clear_screen();
        print_divider();
        printf(BOLD_WHITE " ROUND %d of %d" COLOR_RESET " | " BOLD_GREEN "Hero: %d" COLOR_RESET " - " BOLD_RED "Dark Lord: %d" COLOR_RESET "\n", 
               rounds + 1, BOSS_TOTAL_ROUNDS, hero_wins, dark_lord_wins);
        print_divider();

        printf("\nAvailable moves:\n");
        printf(BOLD_WHITE " [1]" COLOR_RESET " Shield " BOLD_CYAN "(Beats Sword)" COLOR_RESET "\n");
        printf(BOLD_WHITE " [2]" COLOR_RESET " Magic  " BOLD_CYAN "(Beats Shield)" COLOR_RESET "\n");
        printf(BOLD_WHITE " [3]" COLOR_RESET " Sword  " BOLD_CYAN "(Beats Magic)" COLOR_RESET "\n");
        
        int input = get_int_input("\nChoose your move: ", 1, 3);
        BossMove hero_move = (BossMove)input;
        BossMove boss_move = (BossMove)get_random_in_range(1, 3);

        const char *moves[] = {"", "Shield", "Magic", "Sword"};
        
        printf("\n----------------------------------------\n");
        printf(" You chose:      " BOLD_CYAN "%s" COLOR_RESET "\n", moves[hero_move]);
        printf(" Dark Lord uses: " BOLD_MAGENTA "%s" COLOR_RESET "\n", moves[boss_move]);
        printf("----------------------------------------\n");

        int result = resolve_round(hero_move, boss_move);
        if(result == 1) {
            printf(BOLD_GREEN " >> You WIN this round!" COLOR_RESET "\n");
            hero_wins++;
        } else if (result == -1){
            printf(BOLD_RED " >> Dark Lord WINS this round!" COLOR_RESET "\n");
            dark_lord_wins++;
        } else {
            printf(BOLD_YELLOW " >> DRAW! Replaying round..." COLOR_RESET "\n");
            press_enter_to_continue();
            continue; // Don't increment round counter on draw
        }
        rounds++;
        press_enter_to_continue();
    }

    clear_screen();
    if(hero_wins >= BOSS_WINS_NEEDED){
        print_header(BOLD_GREEN "VICTORY" COLOR_RESET);
        printf(BOLD_WHITE " The Dark Lord has been defeated!\n" COLOR_RESET);
        printf(" Peace has returned to the kingdom.\n\n");
        printf(BOLD_MAGENTA " *** CONGRATULATIONS! YOU BEAT THE GAME! *** " COLOR_RESET "\n");
        press_enter_to_continue();
    } else {
        print_header(BOLD_RED "DEFEAT" COLOR_RESET);
        printf(" You have been defeated...\n");
        printf(" Darkness consumes the world.\n\n");
        printf(BOLD_RED " [ GAME OVER ] " COLOR_RESET "\n");
        hero->life_points = 0;
        press_enter_to_continue();
    }
 }