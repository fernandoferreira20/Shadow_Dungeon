#include "combat.h" // This is used for the functions 
#include "../utils/random.h" // This is used for the dice
#include "../utils/input.h" // This is for the valid or invalid input 
#include <stdio.h>
#include <string.h>

// Forward declarations for design
static void display_combat_header(const Enemy* enemy);
static void display_attack_round(int attack_roll, int fatal_strike, int success);
static void display_victory_message(const Enemy* enemy, int coins);
static void display_defeat_message(void);
static CombatResult handle_normal_combat(Player *player, Enemy *enemy);
static CombatResult handle_ancient_dragon(Player *player, Enemy *enemy);

// Here there is the Padovan Sequence
int padovan(int n){
    if(n == 0 || n == 1 || n == 2){
        return 1;
    }
    return padovan(n-2) + padovan(n-3);
}

bool is_in_padovan_sequence(int number){
    for(int i = 0; i < 20; i++){
        int p = padovan(i);
        if(p = number) return true;
        if(p > number) break;
    }
    return false;
}

// Helper functions 
static void display_combat_header(const Enemy* enemy) {
    printf("\n╔══════════════════════════════════════╗\n");
    printf("  ║          COMBAT ENCOUNTER            ║\n");
    printf("  ╠══════════════════════════════════════╣\n");
    printf("  ║ Enemy: %-26s                         ║\n", enemy->name);
    printf("  ║ Defense: %-3d  Damage: %-3d          ║\n", enemy->fatal_strike, enemy->damage);
    printf("  ╚══════════════════════════════════════╝\n\n");
}

static void display_attack_round(int attack_roll, int fatal_strike, int success){
    printf("You roll the dice... %d ", attack_roll);
    if(success){
        printf("> %d ✓\n", fatal_strike);
    } else {
        printf("≤ %d ✗\n", fatal_strike);
    }
}

static void display_victory_message(const Enemy* enemy, int coins){
    printf("\n▓▓▓ VICTORY! ▓▓▓\n");
    printf("You defeated the %s!\n", enemy->name);
    if (coins > 0) printf("+%d coins awarded!\n", coins);
    printf("\n");
}

static void display_defeat_message(void){
    printf("\n☠️  ☠️  ☠️  DEFEAT! ☠️  ☠️  ☠️\n");
    printf("You have been defeated in combat!\n");
    printf("Returning to main menu...\n\n");
}

// Core combat functions
int calculate_hero_attack(const Player *player){
    int attack = roll_dice();
    if(player->has_hero_sword){
        printf("Hero's Sword bonus: +2\n");
        attack += 2;
    } else if(player->has_sword){
        printf("Sword bonus: +1\n");
        attack += 1;
    }
    return attack;
}
// This function is used to apply damage to our player
void apply_damage(Player *player, int damage){
    int actual_damage = damage;
    if(player->has_armor && damage > 0){
        actual_damage = damage - 1;
        if(actual_damage < 1) actual_damage = 1;
        printf("Armor reduces damage from %d to %d\n", damage, actual_damage);
    }
    player->life_points -= actual_damage;
    if(player->life_points < 0) player->life_points = 0;
}
// This function is used to award coins to our player 
void award_coins(Player* player, int coins){
    if(coins > 0){
        player->coins += coins;
        printf("💰 You gained %d coins! Total: %d\n", coins, player->coins);
    }
}

// Handling the combat
static CombatResult handle_normal_combat(Player* player, Enemy* enemy){
    display_combat_message(enemy);
    printf("Your HP: %d | Enemy Defense: %d\n\n", player->life_points, enemy->fatal_strike);

    while(player->life_points > 0 && !enemy->defeated){
        int hero_attack = calculate_hero_attack(player);
        int success = (hero_attack > enemy->fatal_strike);
        display_attack_round(hero_attack, enemy->fatal_strike, success);

        if(success){
            award_coins(player, enemy->coins);
            enemy->defeated = 1;
            display_victory_message(enemy, enemy->coins);
            return COMBAT_VICTORY;
        } else {
            printf("\n%s counterattacks!\n", enemy->name);
            apply_damage(player, enemy->damage);
            printf("Your HP is now: %d\n\n", player->life_points);

            if(player->life_points <= 0){
                display_defeat_message();
                return COMBAT_DEFEAT;
            }
        }

        printf("Press ENTER to coninue...");
        wait_for_enter();
        printf("\n");
    }
    return COMBAT_CONTINUE;
}

static CombatResult handle_ancient_dragon(Player* player, Enemy* enemy){
    printf("\n🐉 🐉 🐉 ANCIENT DRAGON 🐉 🐉 🐉\n");
    printf("The Ancient Dragon asks you a riddle!\n\n");

    int random_number = (roll_dice() * roll_dice() * roll_dice()) % 500 + 1;
    printf("Dragon: Is %d in the Padovan Sequence?\n", random_number);
    printf("Answer [y\n]: ");

    bool player_answer = get_yes_no_input();
    bool correct_answer = is_in_padovan_sequence(random_number);

    printf("\n");

    if(player_answer == correct_answer){
        printf("✓ Correct! The dragon spares you.\n");
        award_coins(player, enemy->coins);
        printf("You find the Hero's Sword in the dragon's hoard!\n");
        player->has_hero_sword = 1;
        player->defeated = 1;
        return COMBAT_VICTORY;
    } else {
        printf("✗ Wrong! The dragon breathes fire!\n");
        printf("The dragon would deal 10 damage...\n");

        int dragon_damage = 10;
        apply_damage(player, dragon->damage);

        if(player->life_points <= 0){
            display_defeat_message();
            return COMBAT_DEFEAT;
        }
        return COMBAT_CONTINUE;
    }
}

// Main combat entry point
CombatResult combat_encounter(Player* player, Enemy* enemy){
    if(strcmp(enemy->name, "Ancient Dragon") == 0){
        return handle_ancient_dragon(player, enemy);
    }

    if(strcmp(enemy->name, "Dark Lord") == 0){
        printf("The Dark Lord must be faced in the final battle!\n");
        return COMBAT_CONTINUE;
    }

    return handle_normal_combat(player, enemy);
}