#ifndef MISSIONS_H
#define MISSIONS_H

// We need player.h to know what a 'Hero' is
#include "../entities/player.h"

// An enum to give clear names to each mission
typedef enum {
    ROTTING_SWAMP,
    HAUNTED_MANSION,
    CRYSTAL_CAVE,
} MissionID;

// --- Function Prototypes for missions.c ---
// Marks a specific mission as complete in the hero's status.
// hero A pointer to the hero whose mission will be marked.
// mission_to_complete The ID of the mission to mark as complete.
void mark_mission_complete(Hero* hero, MissionID mission_to_complete);

// Checks if all 3 preliminary missions are complete.
// hero A pointer to the hero to check.
// 1 (true) if all 3 missions are complete, 0 (false) otherwise.
int are_all_missions_complete(const Hero* hero);

#endif