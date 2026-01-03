 /**
 * @file shop.c
 * @author Otajon 908553
 * @brief  shop menu implementation with helper functions
 */

#include <stdio.h>
#include <stdlib.h>
#include "shop.h"
#include "game_types.h"
#include "utils/utils.h"

#define POTION_PRICE 4
#define SWORD_PRICE 5
#define ARMOR_PRICE 10

/**
 * @param hero Pointer to the Hero structure
 */
static void display_shop_items(const Hero *hero) {
    printf("\n=== SHOP ===\n");
    printf("Your coins: %d\n\n", hero->coins);
    
    printf("1. Health Potion - %d coins\n", POTION_PRICE);
    printf("   Restores up to 6 Life Points (die roll)\n");
    printf("   You have: %d potions\n\n", hero->potions_count);
    
    printf("2. Sword - %d coins\n", SWORD_PRICE);
    printf("   +1 to hero attack (Purchasable once)\n");
    printf("   Status: %s\n\n", hero->has_sword ? "OWNED" : "AVAILABLE");
    
    printf("3. Armor - %d coins\n", ARMOR_PRICE);
    printf("   -1 to enemy damage (Purchasable once)\n");
    printf("   Status: %s\n\n", hero->has_armor ? "OWNED" : "AVAILABLE");
    
    printf("4. Exit Shop\n");
}

void display_shop_menu(Hero *hero) {
    int choice;
    
    while (1) {
        display_shop_items(hero);
        
        // Use our robust utility function
        choice = get_int_input("Select item to purchase [1-4]: ", 1, 4);

        if (choice == 1) {
            purschase_item(hero, ITEM_POTION);
        } else if (choice == 2) {
            purschase_item(hero, ITEM_SWORD);
        } else if (choice == 3) {
            purschase_item(hero, ITEM_ARMOR);
        } else if (choice == 4) {
            printf("Leaving shop...\n");
            return; // Exit the function (and the loop)
        }
        
        press_enter_to_continue();
    }
}

void purschase_item(Hero *hero, ItemType item) {
    int price = 0;
    const char *item_name = "";
    
    /* Determine item details */
    switch (item) {
        case ITEM_POTION:
            price = POTION_PRICE;
            item_name = "Health Potion";
            break;
            
        case ITEM_SWORD:
            price = SWORD_PRICE;
            item_name = "Sword";
            if (hero->has_sword) {
                printf("You already own a Sword!\n");
                return;
            }
            break;
            
        case ITEM_ARMOR:
            price = ARMOR_PRICE;
            item_name = "Armor";
            if (hero->has_armor) {
                printf("You already own Armor!\n");
                return;
            }
            break;
            
        default:
            return;
    }
    
    /* Check if hero has enough coins */
    if (hero->coins < price) {
        printf("Not enough coins! %s costs %d coins. You have %d.\n", 
               item_name, price, hero->coins);
        return;
    }
    
    /* Process the purchase */
    hero->coins -= price;
    
    /* Update hero's inventory */
    switch (item) {
        case ITEM_POTION:
            hero->potions_count++;
            printf("Health Potion purchased! Total: %d.\n", hero->potions_count);
            break;
        case ITEM_SWORD:
            hero->has_sword = true;
            printf("Sword purchased! Attack +1.\n");
            break;
        case ITEM_ARMOR:
            hero->has_armor = true;
            printf("Armor purchased! Damage Taken -1.\n");
            break;
        default: break;
    }
    
    printf("Remaining coins: %d\n", hero->coins);
}