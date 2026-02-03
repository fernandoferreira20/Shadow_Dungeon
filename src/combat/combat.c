/**
 * @file combat.c
 * @author Alexandru 907625
 * @brief Implementation of standard combat and trap logic
 */

#include <stdio.h>
#include "combat.h"
#include "final_boss.h" // We will create this file in the next step!
#include "utils/random.h"
#include "utils/utils.h"

int hero_attack_roll(const Hero *hero){
    int roll = roll_die();
    int bonus = 0;

    if(hero->has_sword) bonus = 1;
    if(hero->has_hero_sword) bonus = 2;

    printf("You rolled %d (Bonus +%d) = Attack %d\n", roll, bonus, roll + bonus);
    return roll + bonus;
}

void apply_trap_effect(Hero *hero, const Enemy *trap){
    printf("\n!!! TRAP !!!\n");
    printf("You triggered: %s\n", trap->name);

    if(trap->fatal_strike_req == 999){
        // Special logic for "Unsafe Bridge" type traps
        printf("The environment is unstable! Flipping a coin...\n");
        if(flip_coin()){ // 1 = Heads
            printf("Heads! You cross safely and find some loot!\n");
            hero->coins += trap->coins_reward;
        } else { // 0 = Tails
            printf("Tails! You slip and take damage!\n");
            hero->life_points -= trap->damage_inflicted;
        }
    } else {
        // Standard damage trap
        printf("You take %d damage!\n", trap->damage_inflicted);
        hero->life_points -= trap->damage_inflicted;
    }
    
    // Check for death immediately
    if (hero->life_points < 0) hero->life_points = 0;
    
    press_enter_to_continue();
}

void fight_enemy(Hero *hero, Enemy *enemy, MissionStatus *status){
    printf("\n--- FIGHT STARTED: Hero vs %s ---\n", enemy->name);

    // --- Special Boss Logic: Ancient Dragon ---
    if(enemy->type == ANCIENT_DRAGON){
        int mystery_num = get_random_in_range(1, 100); // 1-100 is easier for mental math
        printf("The Dragon roars! 'Does the number %d belong to the Padovan sequence?'\n", mystery_num);
        int ans = get_int_input("1. Yes\n0. No\n> ", 0, 1);

        // We assume is_padovan() exists in final_boss.h
        bool is_correct = (ans == is_padovan(mystery_num)); 
        
        if(is_correct){
            printf("Correct! The Dragon is stunned and deals 0 damage this fight!\n");
            enemy->damage_inflicted = 0;
        } else {
            printf("Wrong! The Dragon breathes fire!\n");
        }
    }

    // --- Main Combat Loop ---
    // We fight as long as hero is alive AND the enemy isn't a trap (fatal_req < 100)
    while (hero->life_points > 0) {
        
        // 1. Hero Attacks
        printf("\n[Your Turn]\n");
        int attack = hero_attack_roll(hero);

        // 2. Check Victory
        if(attack >= enemy->fatal_strike_req){
            printf("*** VICTORY! ***\n");
            printf("You defeated the %s!\n", enemy->name);
            printf("Loot: %d coins.\n", enemy->coins_reward);
            hero->coins += enemy->coins_reward;

            // Update Mission Progress
            if(enemy->type == ORC_GENERAL) status->progress_counter++;
            if(enemy->type == GREATER_VAMPIRE) status->is_completed = true;
            
            // Key Drop
            if(enemy->type == GUARDIAN_DEMON && !hero->has_key){
                printf(">>> You found the CASTLE KEY! <<<\n");
                hero->has_key = true;
                status->key_recovered = true;
            }

            // Sword Drop
            if(enemy->type == ANCIENT_DRAGON && !hero->has_hero_sword){
                printf(">>> You claimed the HERO SWORD! <<<\n");
                hero->has_hero_sword = true;
                status->sword_recovered = true;
                status->is_completed = true;
            }

            break; // Exit fight loop
        } 
        
        // 3. Enemy Attacks (if hero missed)
        printf("Missed! (You needed %d)\n", enemy->fatal_strike_req);
        printf("[Enemy Turn]\n");
        
        // Armor reduction
        int dmg = enemy->damage_inflicted;
        if(hero->has_armor && dmg > 0) dmg--;

        printf("The %s attacks! You take %d damage.\n", enemy->name, dmg);
        hero->life_points -= dmg;
        
        if(hero->life_points < 0) hero->life_points = 0;
        printf("Hero HP: %d/%d\n", hero->life_points, MAX_LIFE);

        if(hero->life_points == 0) {
            printf("... You have fallen in battle ...\n");
            break;
        }

        press_enter_to_continue();
    }
}