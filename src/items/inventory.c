/**
 * @file inventory.c
 * @author Otajon 908553
 * @brief Hero inventory management
 */

void display_inventory(const Hero *hero) {
    printf("\n=== HERO INVENTORY ===\n");
    printf("Life Points: %d out of %d\n", hero->life_points, MAX_LIFE);
    printf("Coins: %d\n", hero->coins);
    printf("Potions: %d\n", hero->potions_count);
    
    int has_equipment = hero->has_sword || hero->has_hero_sword || hero->has_armor || hero->has_key;

    if (!has_equipment) {
        printf("- No equipment\n");
   } else {
        printf("\n=== HERO EQUIPMENT ===\n"); 
        if (hero->has_sword) { printf("- Sword\n"); }
        if (hero->has_hero_sword) { printf("- Hero's Sword\n"); }
        if (hero->has_armor) { printf("- Armor\n"); }
        if (hero->has_key) { printf("- Key\n"); }
   }
}

void use_health_potion(Hero *hero) {
    if (hero->potions_count <= 0) { 
        printf("You do not have any health potions!\n");
        return;
    }

    if (hero->life_points >= MAX_LIFE) {
        printf("Your health is full: %d out of %d\n", hero->life_points, MAX_LIFE); 
        return;
    }

    int heal_amount = roll_die();
    int new_life_points = hero->life_points + heal_amount;
    
    if (new_life_points > MAX_LIFE) {
        new_life_points = MAX_LIFE;  
    }
    
    hero->life_points = new_life_points;  
    hero->potions_count--;

    printf("\n=== HEALTH POTION USED ===\n");
    printf("Rolled heal amount: %d\n", heal_amount);
    printf("New Life Points: %d/%d\n", hero->life_points, MAX_LIFE);
    printf("Potions remaining: %d\n", hero->potions_count);
}