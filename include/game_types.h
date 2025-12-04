#ifndef GAME_TYPES.H
#define GAME_TYPES.H

#include <stdbool.h>
#include "game_constants.h" //used for the global constants

/** 
 * @file game_types.h
 * @brief Core data structure and enums for the game
 */

 // Enumerations 

 /** @brief Here we have our hero's items */
 typedef enum {
    ITEM_POTION, // for restoring the health
    ITEM_SWORD, // +1 attack
    ITEM_ARMOR, // -1 damage taken
    ITEM_HERO_SWORD, // +2 attack
    ITEM_KEY // to unlock the Dark Lord's Castle
 } ItemType;

 /** @brief Used to represent the specific mission */
 typedef enum {
    MISSION_SWAMP = 1,
    MISSION_MANSION,
    MISSION_CAVE,
    MISSION_CASTLE
 } MissionType;

 /** @brief This is for the hero's inventory and statistics */
 typedef struct Hero {
    int life_points;
    int coins;
    int potions_count;
    bool has_sword;
    bool has_hero_sword;
    bool has_armor;
    bool has_key;
 } Hero;

 /** @brief Used for tracking the progress of a specific mission */
 typedef struct MissionStatus {
    MissionType type;
    bool is_completed; 
    int progress_counter; // To know how many enemies we defeated 
 } MissionStatus;

 /** @brief Represents a snapshot of the game state for saving */ 
 typedef struct SaveData {
    char data_time[MAX_STRING_LEN];
    int life_points;
    int coins;
    int items_count;
    int completed_missions_count;
    Hero hero_snapshot;
    MissionStatus mission_snapshot[4];
 } SaveData;

 /** @brief Node for the linked list of saved games */
 typedef struct SaveNode {
    SaveData data;  
    struct SaveData *next;
 } SaveNode;

 /** @brief The master game structure holding the active state */
 typedef struct GameData {
    Hero current_hero;
    MissionStatus missions[4]; // tracking all the missions
    SaveNode *save_list_head; // head of the linked lists
    bool cheats_unlocked; // true if the Konami code was entered
 } GameData;

 #endif