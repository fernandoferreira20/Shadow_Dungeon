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
#include "menus/menus.h" 

#define POTION_PRICE 4
#define SWORD_PRICE 5
#define ARMOR_PRICE 10

/**
 * @param hero Pointer to the Hero structure
 */
static void display_shop_items(const Hero *hero) {
    print_header("MERCHANT SHOP");
    printf(BOLD_YELLOW "   Your Purse: %d Coins" COLOR_RESET "\n", hero->coins);
    print_divider();
    
    printf(BOLD_WHITE " [1] Health Potion" COLOR_RESET " ... " BOLD_YELLOW "%d coins" COLOR_RESET "\n", POTION_PRICE);
    printf("     Restores up to 6 HP. (Owned: %d)\n\n", hero->potions_count);
    
    printf(BOLD_WHITE " [2] Iron Sword" COLOR_RESET " ...... " BOLD_YELLOW "%d coins" COLOR_RESET "\n", SWORD_PRICE);
    printf("     +1 Attack.\n");
    printf("     Status: %s\n\n", hero->has_sword ? BOLD_GREEN "OWNED" COLOR_RESET : "Available");
    
    printf(BOLD_WHITE " [3] Chain Armor" COLOR_RESET " ..... " BOLD_YELLOW "%d coins" COLOR_RESET "\n", ARMOR_PRICE);
    printf("     -1 Incoming Dmg.\n");
    printf("     Status: %s\n\n", hero->has_armor ? BOLD_GREEN "OWNED" COLOR_RESET : "Available");
    
    print_divider();
    printf(BOLD_WHITE " [4] Exit Shop" COLOR_RESET "\n");
}

void display_shop_menu(Hero *hero) {
    int choice;
    
    while (1) {
        display_shop_items(hero);
        
        choice = get_int_input("Select item to purchase [1-4]: ", 1, 4);

        if (choice == 1) {
            purschase_item(hero, ITEM_POTION);
        } else if (choice == 2) {
            purschase_item(hero, ITEM_SWORD);
        } else if (choice == 3) {
            purschase_item(hero, ITEM_ARMOR);
        } else if (choice == 4) {
            printf("Leaving shop...\n");
            return; 
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
                printf(BOLD_GREEN "You already own a Sword!" COLOR_RESET "\n");
                return;
            }
            break;
            
        case ITEM_ARMOR:
            price = ARMOR_PRICE;
            item_name = "Armor";
            if (hero->has_armor) {
                printf(BOLD_GREEN "You already own Armor!" COLOR_RESET "\n");
                return;
            }
            break;
            
        default:
            return;
    }
    
    /* Check if hero has enough coins */
    if (hero->coins < price) {
        printf(BOLD_RED "Not enough coins!" COLOR_RESET " %s costs " BOLD_YELLOW "%d" COLOR_RESET ". You have " BOLD_YELLOW "%d" COLOR_RESET ".\n", 
               item_name, price, hero->coins);
        return;
    }
    
    /* Process the purchase */
    hero->coins -= price;
    
    /* Update hero's inventory */
    switch (item) {
        case ITEM_POTION:
            hero->potions_count++;
            printf(BOLD_GREEN "Health Potion purchased!" COLOR_RESET " Total: %d.\n", hero->potions_count);
            break;
        case ITEM_SWORD:
            hero->has_sword = true;
            printf(BOLD_GREEN "Sword purchased!" COLOR_RESET " Attack +1.\n");
            break;
        case ITEM_ARMOR:
            hero->has_armor = true;
            printf(BOLD_GREEN "Armor purchased!" COLOR_RESET " Damage Taken -1.\n");
            break;
        default: break;
    }
    
    printf("Remaining coins: " BOLD_YELLOW "%d" COLOR_RESET "\n", hero->coins);
}