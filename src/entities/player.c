/**
* @file player.c
* @author Fernado 908697
* @brief Implementation of Hero mechanics: creation, stat validation, and death condition checks.
*/

#include "player.h"
#include <stddef.h> // for NULL

Hero create_hero(){
	Hero new_hero;

	// initialze stander state
	new_hero.life_points = 20;
	new_hero.coins = 0;
	new_hero.potions_count = 0;

	// initialze inventory flages to false
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

	// cap life points at 20 (Max)
	if(hero->life_points > 20){
		hero->life_points = 20;
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
	if(hero == NULL){
		return (hero->life_points <= 0);
	}
}