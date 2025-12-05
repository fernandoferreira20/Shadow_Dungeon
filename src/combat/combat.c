/**
 * @file mission_menu.c
 * @author Alexandru 907625
 * @brief Implementation of standard combat and trap logic
 */

#include <stdio.h>
#include "combat.h"
#include "final_boss.h" //used only for Padovan check
#include "../../utils/random.h"
#include "../../utils/utils.h"

int hero_attack_roll(const Hero *hero){
    int roll = roll_die();
    int bonus = 0;

    if(hero->has_sword) bonus = 1;
    if(hero->has_hero_sword) bonus = 2;

    printf("You rolled %d (Bonus +%d) = Attack %d\n", roll, bonus, roll + bonus);
    return roll + bonus;
}

void apply_trap_effect(Hero *hero, const Enemy *trap){
    printf("\nTRAP! You triggered: %s\n", trap->name);

    if(trap->fatal_strike_req == 999){
        printf("The bridge is crumbling! Flipping a coin...\n");
        if(flip_coin(())){ //heads
            printf("Heads! You cross safely and find coins!\n");
            hero->coins += trap->coins_reward;
        } else { //tails
            printf("Tails! You slip and take damage!\n");
            hero->life_points -= trap->damage_inflicted;
        }
    } else {
        printf("You take %d damage!\n", trap->damage_inflicted);
        hero->life_points -= trap->damage_inflicted;
    }
    press_enter_to_continue();
}

void fight_enemy(Hero *hero, Enemy *enemy, MissionStatus *status){
    printf("\n--- FIGHT STARTED: Hero vs %s ---\n", enemy->name);

    if(enemy->type == ANCIENT_DRAGON){
        int mystery_num = get_random_in_range(1, 500);
        printf("The Dragon roars! 'Does the number %d belong to the Padovan sequence?'\n", mystery_num);
        int ans = get_int_input("1. Yes\n0. No\n> ",0, 1);

        // Checking Padovan
        if(ans == is_padovan(mystery_num)){
            printf("Correct! The Dragon is stunned and deals 0 damage this fight!\n");
            enemy->damage_inflicted = 0;

            if(!hero->has_hero_sword){
                printf("You seized the Hero's Sword!\n");
                hero->has_hero_sword = true;
                status->sword_recovered = true;
            }
        } else {
            printf("Wrong! The Dragon breathes fire!\n");
        }
    }

    while (hero->life_points > 0 && enemy->fatal_strike_req < 100){
        // 1. Hero Attacks
        int attack = hero_attack_roll(hero);

        // 2. Compare with Fatal Strike
        if(attack > enemy->fatal_strike_req){
            printf("Victory! You defeated the %s!\n", enemy->name);
            printf("You looted %d coins.\n", enemy->coins_reward);
            hero->coins += enemy->coins_reward;

            // Update the Mission Status

            if(enemy->type == ORC_GENERAL){
                status->progress_counter++;
            }

            if(enemy->type == GREATER_VAMPIRE){
                status->is_completed = true;
            }

            if(enemy->type == GUARDIAN_DEMON){
                if(!hero->has_key){
                    printf("*** You found the Key to the Dark Lord's Castle! ***\n");
                    hero->has_key = true;
                    status->key_recovered = true;
                }
            }

            if(enemy->type == ANCIENT_DRAGON){
                if(!hero->has_hero_sword){
                    printf("*** You found the Hero's Sword! ***\n");
                    hero->has_hero_sword = true;
                    status->sword_recovered = true;
                }
            }
            break;
        } else {
            // 3. Enemy Attacks
            printf("Attack failed! (Needed > %d)\n", enemy->fatal_strike_req);
            printf("The %s attacks! You take %d damage.\n", enemy->name, enemy->damage_inflicted);
            hero->life_points -= enemy->damage_inflicted;
            printf("Hero HP: %d/%d\n", hero->life_points, MAX_LIFE);
        }
        press_enter_to_continue();
    }
}