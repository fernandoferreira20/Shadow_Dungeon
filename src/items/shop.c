/**
 * @file shop.c
 * @author Otajon 908553
 * @brief  shop menu implementation with helper functions
 */

#include <stdio.h>
#include <stdlib.h>
#include "shop.h"
#include "../../include/game_types.h"

#define POTION_PRICE 4
#define SWORD_PRICE 5
#define ARMOR_PRICE 10

/**
 * @param hero Pointer to the Hero structure
 */
static void display_shop_items(Hero *hero) {
    printf("\n=== SHOP ===\n");
    printf("Your coins: %d\n\n", hero->coins);
    
    printf("1. Health Potion - %d coins\n", POTION_PRICE);
    printf("   Restores until 6 Life Points (rolling a 6-sided dice)\n");
    printf("   You have: %d potions\n\n", hero->potions_count);
    
    printf("2. Sword - %d coins\n", SWORD_PRICE);
    printf("   +1 to the hero attack (permanent, purchasable only once)\n");
    printf("   Status: %s\n\n", hero->has_sword ? "OWNED" : "AVAILABLE");
    
    printf("3. Armor - %d coins\n", ARMOR_PRICE);
    printf("   -1 from enemy damage (permanent, purchasable only once)\n");
    printf("   Status: %s\n\n", hero->has_armor ? "OWNED" : "AVAILABLE");
    
    printf("4. Exit Shop\n");
}

void display_shop_menu(Hero *hero) {
    int choice;
    char input[100];
    
    while (1) {
        display_shop_items(hero);
        printf("Select item to purchase [1-4]: ");
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &choice) == 1) {
                if (choice == 1) {
                    purchase_item(hero, ITEM_POTION);
                } else if (choice == 2) {
                    purchase_item(hero, ITEM_SWORD);
                } else if (choice == 3) {
                    purchase_item(hero, ITEM_ARMOR);
                } else if (choice == 4) {
                    printf("Leaving shop...\n");
                    return;
                } else {
                    printf("Invalid choice! Please enter 1-4.\n");
                }
            } else {
                printf("Please enter a number.\n");
            }
        }
        
        printf("Press Enter to continue...");
        while (getchar() != '\n');
    }
}

void purchase_item(Hero *hero, ItemType item) {
    int price;
    const char *item_name;
    
    /* Determine item details */
    switch (item) {
        case ITEM_POTION:
            price = POTION_PRICE;
            item_name = "Health Potion";
            break;
            
        case ITEM_SWORD:
            price = SWORD_PRICE;
            item_name = "Sword";
            
            /* Check if already purchased (one-time only) */
            if (hero->has_sword) {
                printf("You already own a Sword! (Can only purchase once)\n");
                return;
            }
            break;
            
        case ITEM_ARMOR:
            price = ARMOR_PRICE;
            item_name = "Armor";
            
            /* Check if already purchased (one-time only) */
            if (hero->has_armor) {
                printf("You already own Armor! (Can only purchase once)\n");
                return;
            }
            break;
            
        default:
            printf("Error: Invalid item type!\n");
            return;
    }
    
    /* Check if hero has enough coins */
    if (hero->coins < price) {
        printf("Not enough coins! %s costs %d coins, but you have only %d.\n", 
               item_name, price, hero->coins);
        return;
    }
    
    /* Process the purchase */
    hero->coins -= price;
    
    /* Update hero's inventory */
    switch (item) {
        case ITEM_POTION:
            hero->potions_count++;
            printf("Health Potion purchased! You now have %d potion(s).\n", 
                   hero->potions_count);
            break;
            
        case ITEM_SWORD:
            hero->has_sword = true;
            printf("Sword purchased! Your attacks now do +1 damage.\n");
            break;
            
        case ITEM_ARMOR:
            hero->has_armor = true;
            printf("Armor purchased! You now take -1 damage from enemies.\n");
            break;
            
        default:
            break;
    }
    
    printf("Remaining coins: %d\n", hero->coins);
}