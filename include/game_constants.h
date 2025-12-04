#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

/**
 * @file game_constants.h
 * @brief Here we define the global constants and the important numbers used in this game
 */

/** @brief Maximum life points that our hero can have */ 
#define MAX_LIFE 20

/** @brief The cost in coins to return to the village if we don't complete a mission */
#define COST_TO_RETURN_VILLAGE 50

/** @brief The number of mission required to complete to be able to unlock the final boss battle */
#define REQUIRED_MISSIONS 3

/** @brief Maximum number of rooms in a generated dungeon */
#define MAX_DUNGEON_ROOMS 10

/** @brief The room number where mission goals must be forced */
#define FORCED_MISSION_ROOM 7

/** @brief Number of rounds needed to win the last fight */
#define BOSS_WINS_NEEDED 3

/** @brief The total of rounds we are able to play in the last fight */
#define BOSS_TOTAL_ROUNDS 5

/** @brief Maximum lenght for string buffers */
#define MAX_STRING_LEN 50

#endif 