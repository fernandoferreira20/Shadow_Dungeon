/**
* @file village.c
* @author Fernado 908697
* @brief Implementation of the central hub mechanics, including menu display, healing logic, and exit routines.
*/

#include "village.h"
#include <stdio.h>
#include <stddef.h> // For NULL

void display_village_menu(GameData *data){
    if(data == NULL) return;

    printf("\n=============================\n");
    printf("         VILLAGE HUB         \n");
    printf("=============================\n");
    // Update variable: current_hero
    printf("Hero Stats: HP %d/20 | Coins: %d\n", data->current_hero.life_points, data->current_hero.coins);

    if(data->current_hero.has_sword) printf("[Euipped: Iron Sword]\n");
    if(data->current_hero.has_hero_sword) printf("[Euipped: HERO SWORD]\n");

    printf("-----------------------------\n");
    printf("1. Start a Mission\n");   
    printf("2. Rest (Restore Life)\n");   
    printf("3. Inventory\n");   
    printf("4. Save Game\n");   
    printf("5. Exit\n");   
    printf("-----------------------------\n");
    printf("Select an option: ");   
}

void rest_in_village(Hero *hero){
    if(hero == NULL) return;
    
    // Restore to MAX_LIFE (20)
    hero->life_points = 20;
    
    printf("\n[Innkeeper]: You look tired, traveler. Take a rest here.\n");
    printf("* You slept soundly. You health is fully restored to 20 HP! *\n");
}

void perform_exit_sequence(GameData *data){
    printf("\n-----------------------------\n");
    printf("Leaving the world...\n");
    printf("Remeber to save the game so you do not lose your progress!\n");
    printf("Goodbye, Hero.\n");
    
}