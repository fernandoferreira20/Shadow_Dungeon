/**
 * @file inventory.c
 * @author Otajon 908553
 * @brief Hero inventory management
 */

#include "inventory.h"
#include "utils/random.h" 
#include "utils/utils.h" 
#include "menus/menus.h" 
#include <stdio.h>

void display_inventory(const Hero *hero) {
    print_header("HERO INVENTORY");

    // Visual stats block
    printf(BOLD_WHITE " [ STATUS ]" COLOR_RESET "\n");
    // Heart symbol (ascii compatible) or just text with Red
    printf(" " BOLD_RED "Health :" COLOR_RESET " " BOLD_GREEN "%d" COLOR_RESET "/" BOLD_GREEN "%d" COLOR_RESET "\n", hero->life_points, MAX_LIFE);
    printf(" " BOLD_YELLOW "Coins  :" COLOR_RESET " " BOLD_YELLOW "%d" COLOR_RESET "\n", hero->coins);
    printf(" " BOLD_MAGENTA "Potions:" COLOR_RESET " %d\n", hero->potions_count);
    
    // Check if we have any unique items
    bool has_equipment = hero->has_sword || hero->has_hero_sword || hero->has_armor || hero->has_key;

    printf("\n" BOLD_WHITE " [ EQUIPMENT ]" COLOR_RESET "\n");
    if (!has_equipment) {
        printf(COLOR_RED " (Empty)" COLOR_RESET "\n");
   } else {
        if (hero->has_sword) { printf(" - " BOLD_CYAN "Sword" COLOR_RESET " (+1 Atk)\n"); }
        if (hero->has_hero_sword) { printf(" - " BOLD_CYAN "Hero's Sword" COLOR_RESET " (+2 Atk)\n"); }
        if (hero->has_armor) { printf(" - " BOLD_BLUE "Armor" COLOR_RESET " (-1 Dmg)\n"); }
        if (hero->has_key) { printf(" - " BOLD_YELLOW "Dungeon Key" COLOR_RESET "\n"); }
   }
   print_divider();
}

void use_health_potion(Hero *hero) {
    if (hero->potions_count <= 0) { 
        printf(BOLD_RED " [!] You do not have any health potions!" COLOR_RESET "\n");
        return;
    }

    if (hero->life_points >= MAX_LIFE) {
        printf(BOLD_GREEN " Your health is already full (%d/%d)." COLOR_RESET "\n", hero->life_points, MAX_LIFE); 
        return;
    }

    // Mechanics: Roll a die to see how much we heal
    int heal_amount = roll_die();
    int new_life_points = hero->life_points + heal_amount;
    
    if (new_life_points > MAX_LIFE) {
        new_life_points = MAX_LIFE;  
    }
    
    hero->life_points = new_life_points;  
    hero->potions_count--;

    printf("\n" BOLD_MAGENTA "=== POTION USED ===" COLOR_RESET "\n");
    printf(" Die Rolled: " BOLD_WHITE "[ %d ]" COLOR_RESET "\n", heal_amount);
    printf(" Healing... " BOLD_GREEN "+%d HP" COLOR_RESET "\n", heal_amount);
    printf(" Current Health: " BOLD_GREEN "%d/%d" COLOR_RESET "\n", hero->life_points, MAX_LIFE);
    printf(" Potions left: %d\n", hero->potions_count);
}