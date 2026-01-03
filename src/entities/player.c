/**
* @file player.c
* @author Fernado 908697
* @brief Implementation of Hero mechanics: creation, stat validation, and death condition checks.
*/

#include "player.h"
#include <stddef.h> // for NULL

Hero create_hero(){
	Hero new_hero;

	// Initialize stander state
	new_hero.life_points = MAX_LIFE;
	new_hero.coins = 0;
	new_hero.potions_count = 0;

	// Initialize inventory flags to false
	new_hero.has_sword = false;
	new_hero.has_hero_sword = false;
	new_hero.has_armor = false;
	new_hero.has_key = false;

	return new_hero;
}

void update_hero_stats(Hero *hero, int life_delta, int coin_delta){
	if(hero == NULL) return;

	// apply life change
	hero->life_points += life_delta;

	// cap life points at MAX_LIFE
	if(hero->life_points > MAX_LIFE){
		hero->life_points = MAX_LIFE;
	}

	// cap life points at 0 (Min)
	if(hero->life_points < 0){
		hero->life_points = 0;
	}

	// apply coin change
	hero->coins += coin_delta;

	// prevent negative coins
	if(hero->coins < 0){
		hero->coins = 0;
	}
}

bool is_hero_dead(const Hero *hero){
	// Safety check: if the pointer is null, consider it "dead" or invalid
	if(hero == NULL){
		return true;
	}
	// Return the result of the comparison
	return (hero->life_points <= 0);
}