#include "player.h" // include our header file
#include <stdio.h> // we will need this for 'display_inventory' later

// this are the starting values
#define STARTING_LIFE 20
#define STARTING_COINS 0
#define STARTING_MISSIONS 0
#define STARTING_ITEMS 0

// Sets a hero's stats to the default new game values.
void initialize_new_hero(Hero* hero){
	// we check if the pointer is valide just in case
	if(hero == NULL){
		return; // safety check
	}

	// set the main hero status
	hero->life_points = STARTING_LIFE; // 20 life points
	hero->coins = STARTING_COINS; // 0 coins

	// Set all mission statuses to 0 (not complete)
    hero->missions.rotting_swamp = 0;
    hero->missions.haunted_mansion = 0; 
    hero->missions.crystal_cave = 0;

	// set all the inventory items to 0
	hero->inventory.health_potions = STARTING_ITEMS;
	hero->inventory.has_sword = STARTING_ITEMS;
	hero->inventory.has_armor = STARTING_ITEMS;
	hero->inventory.has_castle_key = STARTING_ITEMS;
	hero->inventory.has_heros_sword = STARTING_ITEMS;
}

// displays the hero's current stats and inventory
void display_inventory(const Hero* hero){
	// we check if the pointer is valide just in case
	if(hero == NULL){
		return; // safe check
	}

	printf("\n ---- HERO INVENTORY ---- \n");
	printf("Life Points: %d / %d\n", hero->life_points, STARTING_LIFE); // show current / max
	printf("Coins:       %d\n", hero->coins);
	printf("----------------------------\n");
	printf("Items: \n");
	
	// prints item counts
	printf(" - Health Potions: %d\n", hero->inventory.health_potions);

	// print the equipament (only if the hero have it)	
	if(hero->inventory.has_heros_sword){
		printf(" - Hero's Sword (Equipped)\n");	
	}else if(hero->inventory.has_sword){
		printf(" - Sword (Equipped)\n");	
	}else{
		printf(" - No Weapon\n");
	}

	if(hero->inventory.has_armor){
		printf(" - Armor (Equipped)\n");
	}else{
		printf(" - No Armor\n");
	}

	// print key items
	printf("Key Item:\n");
	if(hero->inventory.has_castle_key){
		printf(" - Key to the Dark Lord's Castle\n");
	}else{
		printf(" - (No key items)\n");
	}
	printf("-----------------------------\n\n");
}