#ifndef MISSIONS_H
#define MISSIONS_H

#include "../../include/game_types.h"

/**
 * @file missions.h
 * @brief Managing mission selection and tracking the progress
 */

/**
 * @brief Initialize the standard missions in the GameData
 * @param missions Array of MissionStatus to initialize
 */
void initialize_missions(MissionStatus missions[4]);

/**
 * @brief Display the Menu to select the missions
 * @param data Pointer to GameData to check completion status
 * @return The selected mission index (or 0 to cancel)
 */
int select_mission(const GameData *data);

/**
 * @brief Mark a mission as completed
 * @param mission Pointer to the specific MissionStatus to update
 */
void mark_mission_complete(MissionStatus *mission);

#endif