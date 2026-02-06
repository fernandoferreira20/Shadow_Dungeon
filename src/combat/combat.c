/**
 * @file combat.c
 * @author Alexandru 907625
 * @brief Implementation of standard combat and trap logic
 */

#include <stdio.h>
#include "combat.h"
#include "final_boss.h" 
#include "utils/random.h"
#include "utils/utils.h"
#include "menus/menus.h" 

// helper function to draw the combat HUB
void print_combat_hub(const Hero *hero, const Enemy *enemy){
    clear_screen();
    // Replaced manual lines with the consistent divider style
    print_divider();
    printf(BOLD_RED "   ⚔️  COMBAT: Hero vs %s  ⚔️" COLOR_RESET "\n", enemy->name);
    print_divider();
    
    printf(" HERO HP: [");
    // Visual Health Bar: Bold Green '#' for health, dimmed Red '-' for missing health
    for(int i=0; i<MAX_LIFE; i++) {
        if(i < hero->life_points) printf(BOLD_GREEN "#" COLOR_RESET);
        else printf(BOLD_RED "-" COLOR_RESET);
    }
    printf("] " BOLD_WHITE "%d/%d" COLOR_RESET "\n", hero->life_points, MAX_LIFE);
    print_divider();
    printf("\n");
}

int hero_attack_roll(const Hero *hero){
    int roll = roll_die();
    int bonus = 0;

    if(hero->has_sword) bonus = 1;
    if(hero->has_hero_sword) bonus = 2;

    printf(" You rolled " BOLD_WHITE "[%d]" COLOR_RESET " (Bonus +%d) = " BOLD_CYAN "Attack Power %d" COLOR_RESET "\n", roll, bonus, roll + bonus);
    return roll + bonus;
}

void apply_trap_effect(Hero *hero, const Enemy *trap){
    clear_screen(); 
    print_divider();
    printf(BOLD_RED "       !!! TRAP TRIGGERED !!!       " COLOR_RESET "\n");
    print_divider();
    
    printf(" You stumbled into: " BOLD_YELLOW "%s" COLOR_RESET "\n\n", trap->name);

    if(trap->fatal_strike_req == 999){
        // Special logic for "Unsafe Bridge" type traps
        printf(" The environment is unstable! Flipping a coin...\n");
        press_enter_to_continue();
        
        if(flip_coin()){ // 1 = Heads
            printf(" " BOLD_GREEN "Heads! You cross safely and find some loot!" COLOR_RESET "\n");
            hero->coins += trap->coins_reward;
        } else { // 0 = Tails
            printf(" " BOLD_RED "Tails! You slip and take damage!" COLOR_RESET "\n");
            hero->life_points -= trap->damage_inflicted;
        }
    } else {
        // Standard damage trap
        printf(" You take " BOLD_RED "%d damage!" COLOR_RESET "\n", trap->damage_inflicted);
        hero->life_points -= trap->damage_inflicted;
    }
    
    // Check for death immediately
    if (hero->life_points < 0) hero->life_points = 0;
    
    press_enter_to_continue();
}

void fight_enemy(Hero *hero, Enemy *enemy, MissionStatus *status){
    // --- Special Boss Logic: Ancient Dragon ---
    if(enemy->type == ANCIENT_DRAGON){
        clear_screen();
        print_header(BOLD_RED "THE ANCIENT DRAGON AWAKENS..." COLOR_RESET);
        
        int mystery_num = get_random_in_range(1, 100);
        printf(BOLD_YELLOW "The Dragon roars!" COLOR_RESET " 'Does the number " BOLD_WHITE "%d" COLOR_RESET " belong to the Padovan sequence?'\n", mystery_num);
        int ans = get_int_input(BOLD_CYAN "1. Yes\n0. No\n> " COLOR_RESET, 0, 1);

        bool is_correct = (ans == is_padovan(mystery_num)); 
        
        if(is_correct){
            printf("\n" BOLD_GREEN "Correct! The Dragon is stunned and deals 0 damage this fight!" COLOR_RESET "\n");
            enemy->damage_inflicted = 0;
        } else {
            printf("\n" BOLD_RED "Wrong! The Dragon breathes fire!" COLOR_RESET "\n");
        }
        press_enter_to_continue();
    }

    // --- Main Combat Loop ---
    while (hero->life_points > 0) {
        
        // DRAW THE INTERFACE
        print_combat_hub(hero, enemy);

        // 1. Hero Attacks
        printf(BOLD_WHITE " [ Your Turn ]" COLOR_RESET "\n");
        int attack = hero_attack_roll(hero);

        // 2. Check Victory
        if(attack >= enemy->fatal_strike_req){
            printf("\n" BOLD_GREEN " *** VICTORY! *** " COLOR_RESET "\n");
            printf(" You defeated the %s!\n", enemy->name);
            printf(" Loot: " BOLD_YELLOW "%d coins." COLOR_RESET "\n", enemy->coins_reward);
            hero->coins += enemy->coins_reward;

            // Update Mission Progress
            if(enemy->type == ORC_GENERAL) status->progress_counter++;
            if(enemy->type == GREATER_VAMPIRE) status->is_completed = true;
            
            // Key Drop
            if(enemy->type == GUARDIAN_DEMON && !hero->has_key){
                printf("\n >>> You found the " BOLD_MAGENTA "CASTLE KEY!" COLOR_RESET " <<<\n");
                hero->has_key = true;
                status->key_recovered = true;
            }

            // Sword Drop
            if(enemy->type == ANCIENT_DRAGON && !hero->has_hero_sword){
                printf("\n >>> You claimed the " BOLD_MAGENTA "HERO SWORD!" COLOR_RESET " <<<\n");
                hero->has_hero_sword = true;
                status->sword_recovered = true;
                status->is_completed = true;
            }
            
            press_enter_to_continue(); 
            break; 
        } 
        
        // 3. Enemy Attacks (if hero missed)
        printf(BOLD_RED " Missed!" COLOR_RESET " (You needed %d)\n", enemy->fatal_strike_req);
        printf("\n" BOLD_WHITE " [ Enemy Turn ]" COLOR_RESET "\n");
        
        // Armor reduction
        int dmg = enemy->damage_inflicted;
        if(hero->has_armor && dmg > 0) {
            dmg--;
            printf(" (Armor blocked 1 damage)\n");
        }

        printf(" The %s attacks! You take " BOLD_RED "%d damage." COLOR_RESET "\n", enemy->name, dmg);
        hero->life_points -= dmg;
        
        if(hero->life_points < 0) hero->life_points = 0;

        if(hero->life_points == 0) {
            printf("\n" BOLD_RED "... You have fallen in battle ..." COLOR_RESET "\n");
            press_enter_to_continue();
            break;
        }

        press_enter_to_continue();
    }
}