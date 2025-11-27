#include "combat.h"
#include "../utils/random.h"
#include <stdio.h>

CombatResult combat_encounter(Player *player, Enemy *enemy){
    printf("\n=== COMBAT ===\n");
    printf("You encounter a %s!\n", enemy->name);

    while(player->life_points > 0 && enemy->defetead == false){
        int hero_attack = calculate_hero_attack(player);
        printf("You roll the dice ... Result: %d\n", hero_attack);

        if(hero_attack > enemy->fatal_strike){
            printf("You defeated the %s!\n", enemy->name);
            award_coins(player, enemy->coins);
            enemy->defeated = true;
            return COMBAT_VICTORY;
        } else {
            printf("Attack failed! (%d < %d)\n", hero_attack, enemy->fatal_strike);
            //enemy counterattack 
            printf("%s deals %d damage to you.\n", enemy->name, enemy->damage);
            apply_damage(player, enemy->damage);
            printf("You have %d life points remaining.\n\n", player->life_points);

            if(player->life_points <= 0){
                return COMBAT_DEFEAT;
            }
        }
    }

    return COMBAT_CONTINUE;
}

int calculate_hero_attack(const Player *player){
    int base_attack = roll_dice();

    if(player->has_hero_sword){
        base_attack += 2;
    } else if(player->has_sword){
        base_attack +=1;
    }
    return base_attack;
}

void apply_damage(Player *player, int damage){
    if(player->has_armor){
        damage = (damage > 0) ? damage - 1 : 0;
    }

    player->life_points -= damage;
    if(player->life_points < 0){
        player->life_points = 0;
    }
}

void award_coins(Player *player, int coins){
    player->coins += coins;
    printf("You gained %d coins! Total: %d\n", coins, player->coins);
}

int padovan(int n){
    if(n == 0 || n == 1 || n == 2){
        return 1;
    }
    return padovan(n-2) + padovan(n-3);
}

bool is_in_padovan_sequence(int number){
    for (int i = 0; i < 20; i++){
        int p = padovan(i);
        if(p == number){
            return true;
        }

        if(p>number){
            break;
        }
    }
    return false;
}