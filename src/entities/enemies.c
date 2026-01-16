/**
* @file enemies.c
* @author Fernado 908697
* @brief Implementation of the Enemy Factory.
*/

#include "enemies.h"
#include <string.h>
#include <stdio.h>

Enemy create_enemy(EnemyType type){
    Enemy e;
    e.type = type;

    switch(type){
        // --- Rotting Swamp --
        case WILD_DOG:
            strcpy(e.name, "Wild Dog");
            e.fatal_strike_req = 2;
            e.damage_inflicted = 1;
            e.coins_reward = 0;
            break;
        case GOBLIN:
            strcpy(e.name, "Goblin Scout");
            e.fatal_strike_req = 3;
            e.damage_inflicted = 2;
            e.coins_reward = 2;
            break;
        case SKELETON:
            strcpy(e.name, "Rotted Skeleton");
            e.fatal_strike_req = 4;
            e.damage_inflicted = 2;
            e.coins_reward = 4;
            break;
        case ORC:
            strcpy(e.name, "Orc Warrior");
            e.fatal_strike_req = 3;
            e.damage_inflicted = 4;
            e.coins_reward = 6;
            break;
        case ORC_GENERAL:
            strcpy(e.name, "Orc General (Mini-Boss)");
            e.fatal_strike_req = 6;
            e.damage_inflicted = 3;
            e.coins_reward = 12;
            break;
        
        // --- Haunted Mansion ---
        case BAT:
            strcpy(e.name, "Vampire Bat");
            e.fatal_strike_req = 2;
            e.damage_inflicted = 2;
            e.coins_reward = 1;
            break;
        case ZOMBIE:
            strcpy(e.name, "Shambling Zombie");
            e.fatal_strike_req = 3;
            e.damage_inflicted = 2;
            e.coins_reward = 2;
            break;
        case PHANTOM:
            strcpy(e.name, "Phantom");
            e.fatal_strike_req = 5;
            e.damage_inflicted = 2;
            e.coins_reward = 4;
            break;
        case GREATER_VAMPIRE:
            strcpy(e.name, "Greater Vampire");
            e.fatal_strike_req = 4;
            e.damage_inflicted = 4;
            e.coins_reward = 7;
            break;
        case GUARDIAN_DEMON:
            strcpy(e.name, "Guardian Demon");
            e.fatal_strike_req = 4;
            e.damage_inflicted = 6;
            e.coins_reward = 10;
            break;
        
        // --- Crystal Cave ---
        case ANCIENT_DRAGON:
            strcpy(e.name, "Ancient Dragon");
            e.fatal_strike_req = 0;
            e.damage_inflicted = 0;
            e.coins_reward = 0;
            break;
        
        // --- Final Boss ---
        case DARK_LORD:
            strcpy(e.name, "The Dark Lord");
            e.fatal_strike_req = 6; 
            e.damage_inflicted = 0;
            e.coins_reward = 1000;
            break;
        
        default:
            strcpy(e.name, "Unknown Entity");
            e.fatal_strike_req = 1;
            e.damage_inflicted = 1;
            e.coins_reward = 0;
            break;    
    }
    return e;
}